#ifndef __PID_H
#define __PID_H
#include <stdint.h>

//#include "bsp_dwt.h"

// PID 优化环节使能标志位,通过位与可以判断启用的优化环节;也可以改成位域的形式
typedef enum PID_IMPROVEMENT_E{
	PID_IMPROVE_NONE = 0x00,                 // 无优化
  PID_INTEGRAL_LIMIT = 0x01,               // 积分限幅
  PID_DERIVATIVE_ON_MEASUREMENT = 0x02,    // 微分先行
  PID_TRAPEZOID_INTERGRAL = 0x04,          // 梯形积分
  PID_PROPORTIONAL_ON_MEASUREMENT = 0x08,  // 比例先行
  PID_OUTPUT_FILTER = 0x10,                // 输出滤波
  PID_CHANGING_INTEGRATION_RATE = 0x20,    // 变速积分
  PID_DERIVATIVE_FILTER = 0x40,            // 微分滤波
  PID_ERROR_HANDLE = 0x80,                 // 堵转检测
  PID_DELTA = 0x100,                       // 增量式PID
}PID_IMPROVEMENT_E;

/* PID 报错类型枚举*/
enum ERROR_TYPE_E { PID_ERROR_NONE = 0x00U, PID_MOTOR_BLOCKED_ERROR = 0x01U };

typedef struct{
  uint64_t ERRORCount;
  enum ERROR_TYPE_E ERRORType;
}PidErrorHandlerT;
/* 用于PID初始化的结构体*/
typedef struct PidInitConfigS{
			float Kp;
			float Ki;
			float Kd;
			float Kf;
			float MaxOut;    // 输出限幅
			float DeadBand;  // 死区
			PID_IMPROVEMENT_E Improve;
			float IntegralLimit;  // 积分限幅
			float CoefA;  // AB为变速积分参数,变速积分实际上就引入了积分分离
			float CoefB;          // ITerm = Err*((A-abs(err)+B)/A)  when B<|err|<A+B
			float Output_LPF_RC;  // RC = 1/omegac
			float Derivative_LPF_RC;
		}PidInitConfigS;
typedef struct{
		PidInitConfigS Config;
		/*PID对象的属性*/
		
		float Measure;
		float Last_Measure;
		float Err;
		float Last_Err;
		float Last_Err2;
		float Last_ITerm;

		float Pout;
		float Iout;
		float Dout;
		float Fout;
		float ITerm;

		float Output;
		float Last_Output;
		float Last_Dout;

		float Ref;

		uint32_t DWT_CNT;
		float dt;

		PidErrorHandlerT ERRORHandler;
}PIDClass;
  /**
   * @brief 计算PID输出
   *
   * @param measure 反馈值
   * @param ref     设定值
   * @return float  PID计算输出
   */

	void PID_Init(PIDClass* pid);

  float PIDCalculate(PIDClass* pid,float measure, float ref);
  /* 下面是pid优化环节的实现*/
  // 梯形积分
  void FTrapezoidIntergral(PIDClass* pid);
  // 变速积分(误差小时积分作用更强)
  void FChangingIntegrationRate(PIDClass* pid);
  void FIntegralLimit(PIDClass* pid);
  // 微分先行(仅使用反馈值而不计参考输入的微分)
  void FDerivativeOnMeasurement(PIDClass* pid);
  // 微分滤波(采集微分时,滤除高频噪声)
  void FDerivativeFilter(PIDClass* pid);
  // 输出滤波
  void FOutputFilter(PIDClass* pid);
  // 输出限幅
  void FOutputLimit(PIDClass* pid);
  // 堵转检测
  void FPidErrorHandle(PIDClass* pid);
  // 初始化pid内部参数
  void FInitPid(PIDClass* pid);

#endif
