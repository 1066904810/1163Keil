#include "pid.h"
#include <math.h>

 float PIDCalculate(PIDClass* pid,float measure, float ref) {  // 堵转检测
  if (pid->Config.Improve & PID_ERROR_HANDLE) {
    FPidErrorHandle(pid);
  }
	pid->dt=1;
//  dt = DWT_GetDeltaT(&DWT_CNT);  // 获取两次pid计算的时间间隔,用于积分和微分

  // 保存上次的测量值和误差,计算当前error
  pid->Measure = measure;
  pid->Ref = ref;
  pid->Err = pid->Ref - pid->Measure;

  // 如果在死区外,则计算PID
  if (fabs(pid->Err) > pid->Config.DeadBand) {
    if (pid->Config.Improve != PID_DELTA) {
      // 基本的pid计算,使用位置式
      pid->Pout = pid->Config.Kp * pid->Err;
      pid->ITerm = pid->Config.Ki * pid->Err * pid->dt;
      pid->Dout = pid->Config.Kd * (pid->Err - pid->Last_Err) / pid->dt;

      // 梯形积分
      if (pid->Config.Improve & PID_TRAPEZOID_INTERGRAL) {
        FTrapezoidIntergral(pid);
      }
      // 变速积分
      if (pid->Config.Improve & PID_CHANGING_INTEGRATION_RATE) {
        FChangingIntegrationRate(pid);
      }
      // 微分先行
      if (pid->Config.Improve & PID_DERIVATIVE_ON_MEASUREMENT) {
        FDerivativeOnMeasurement(pid);
      }
      // 微分滤波器
      if (pid->Config.Improve & PID_DERIVATIVE_FILTER) {
        FDerivativeFilter(pid);
      }
      // 积分限幅
      if (pid->Config.Improve & PID_INTEGRAL_LIMIT) {
        FIntegralLimit(pid);
      }

      pid->Iout += pid->ITerm;                                // 累加积分
      pid->Fout = pid->Config.Kf * (pid->Measure - pid->Last_Measure);  // 前馈
      pid->Output = pid->Pout + pid->Iout + pid->Dout + pid->Fout;           // 计算输出

      // 输出滤波
      if (pid->Config.Improve & PID_OUTPUT_FILTER) {
        FOutputFilter(pid);
      }

    } else {
      // 增量式PID
      pid->Pout = pid->Config.Kp * (pid->Err - pid->Last_Err);
      pid->ITerm = pid->Config.Ki * pid->Err;
      pid->Dout = pid->Config.Kd * (pid->Err - 2 * pid->Last_Err + pid->Last_Err2);
      pid->Iout += pid->ITerm;                              // 累加积分
      pid->Output = pid->Last_Output + pid->Pout + pid->Iout + pid->Dout;  // 计算输出
      pid->Last_Err2 = pid->Last_Err;
    }
    // 输出限幅
    FOutputLimit(pid);
  } else  // 进入死区, 则清空积分和输出
  {
    pid->Output = 0;
    pid->ITerm = 0;
  }

  // 保存当前数据,用于下次计算
  pid->Last_Measure = pid->Measure;
  pid->Last_Output = pid->Output;
  pid->Last_Dout = pid->Dout;
  pid->Last_Err = pid->Err;
  pid->Last_ITerm = pid->ITerm;

  return pid->Output;
}

void FTrapezoidIntergral(PIDClass* pid) {
  // 计算梯形的面积,(上底+下底)*高/2
  pid->ITerm = pid->Config.Ki * ((pid->Err + pid->Last_Err) / 2) * pid->dt;
}

void FChangingIntegrationRate(PIDClass* pid) {
  if (pid->Err * pid->Iout > 0) {
    // 积分呈累积趋势
    if (fabs(pid->Err) <= pid->Config.CoefB) {
      return;  // Full integral
    }
    if (fabs(pid->Err) <= (pid->Config.CoefA + pid->Config.CoefB)) {
      pid->ITerm *= (pid->Config.CoefA - fabs(pid->Err) + pid->Config.CoefB) / pid->Config.CoefA;
    } else {  // 最大阈值,不使用积分
      pid->ITerm = 0;
    }
  }
}

void FIntegralLimit(PIDClass* pid) {
  float temp_output = 0, temp_iout = 0;
  temp_iout = pid->Iout + pid->ITerm;
  temp_output = pid->Pout + pid->Iout + pid->Dout;
  if (fabs(temp_output) > pid->Config.MaxOut) {
    if (pid->Err * pid->Iout > 0)  // 积分却还在累积
    {
      pid->ITerm = 0;  // 当前积分项置零
    }
  }

  if (temp_iout > pid->Config.IntegralLimit) {
    pid->ITerm = 0;
    pid->Iout = pid->Config.IntegralLimit;
  }
  if (temp_iout < -pid->Config.IntegralLimit) {
    pid->ITerm = 0;
    pid->Iout = -pid->Config.IntegralLimit;
  }
}

void FDerivativeOnMeasurement(PIDClass* pid) {
  pid->Dout = pid->Config.Kd * (pid->Last_Measure - pid->Measure) / pid->dt;
}

void FDerivativeFilter(PIDClass* pid) {
  pid->Dout = pid->Dout * pid->dt / (pid->Config.Derivative_LPF_RC + pid->dt) +
         pid->Last_Dout * pid->Config.Derivative_LPF_RC / (pid->Config.Derivative_LPF_RC + pid->dt);
}

void FOutputFilter(PIDClass* pid) {
  pid->Output = pid->Output * pid->dt / (pid->Config.Output_LPF_RC + pid->dt) +
           pid->Last_Output * pid->Config.Output_LPF_RC / (pid->Config.Output_LPF_RC + pid->dt);
}

void FOutputLimit(PIDClass* pid) {
  if (pid->Output > pid->Config.MaxOut) {
    pid->Output = pid->Config.MaxOut;
  }
  if (pid->Output < -(pid->Config.MaxOut)) {
    pid->Output = -(pid->Config.MaxOut);
  }
}

void FPidErrorHandle(PIDClass* pid) { /*Motor Blocked Handle*/
  if (fabsf(pid->Output) < pid->Config.MaxOut * 0.001f || fabsf(pid->Ref) < 0.0001f) {
    return;
  }

  if ((fabsf(pid->Ref - pid->Measure) / fabsf(pid->Ref)) > 0.95f) {
    // Motor blocked counting
    pid->ERRORHandler.ERRORCount++;
  } else {
    pid->ERRORHandler.ERRORCount = 0;
  }

  if (pid->ERRORHandler.ERRORCount > 500) {
    // Motor blocked over 1000times
    pid->ERRORHandler.ERRORType = PID_MOTOR_BLOCKED_ERROR;
  }
}

void FInitPid(PIDClass* pid) {
  pid->Pout = 0;
  pid->Iout = 0;
  pid->Dout = 0;
  pid->ITerm = 0;
  pid->Output = 0;
  pid->Last_Output = 0;
  pid->Last_Dout = 0;
  pid->Last_ITerm = 0;
  pid->Last_Measure = 0;
  pid->Last_Err = 0;
  pid->Last_Err2 = 0;
//  DWT_GetDeltaT(&DWT_CNT);
}
