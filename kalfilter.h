#pragma once

#include <cstdint>
#include <functional>

#include "arm_math.h"
#ifndef user_malloc
#ifdef _CMSIS_OS_H
#define user_malloc pvPortMalloc
#else
#define user_malloc malloc
#endif
#endif
// 若运算速度不够,可以使用q31代替f32,但是精度会降低
#define mat arm_matrix_instance_f32
#define Matrix_Init arm_mat_init_f32
#define Matrix_Add arm_mat_add_f32
#define Matrix_Subtract arm_mat_sub_f32
#define Matrix_Multiply arm_mat_mult_f32
#define Matrix_Transpose arm_mat_trans_f32
#define Matrix_Inverse arm_mat_inverse_f32
namespace Component {
class KalmanFilter {
 public:
  float *FilteredValue = 0;
  float *MeasuredVector = 0;
  float *ControlVector = 0;

  uint8_t xhatSize = 0;
  uint8_t uSize = 0;
  uint8_t zSize = 0;

  uint8_t UseAutoAdjustment = 0;
  uint8_t MeasurementValidNum = 0;

  uint8_t *MeasurementMap = 0;  // 量测与状态的关系 how measurement relates to
                                // the state
  float *MeasurementDegree = 0;  // 测量值对应H矩阵元素值 elements of each
                                 // measurement in H
  float *MatR_DiagonalElements = 0;  // 量测方差 variance for each measurement
  float *StateMinVariance = 0;  // 最小方差 避免方差过度收敛 suppress filter
                                // excessive convergence
  uint8_t *temp = 0;

  // 配合用户定义函数使用,作为标志位用于判断是否要跳过标准KF中五个环节中的任意一个
  uint8_t SkipEq1, SkipEq2, SkipEq3, SkipEq4, SkipEq5;

  // definiion of struct mat: rows & cols & pointer to vars
  mat xhat;       // x(k|k)
  mat xhatminus;  // x(k|k-1)
  mat u;          // control vector u
  mat z;          // measurement vector z
  mat P;          // covariance matrix P(k|k)
  mat Pminus;     // covariance matrix P(k|k-1)
  mat F, FT;      // state transition matrix F FT
  mat B;          // control matrix B
  mat H, HT;      // measurement matrix H
  mat Q;          // process noise covariance matrix Q
  mat R;          // measurement noise covariance matrix R
  mat K;          // kalman gain  K
  mat S, temp_matrix, temp_matrix1, temp_vector, temp_vector1;

  int8_t MatStatus;

  // 用户定义函数,可以替换或扩展基准KF的功能
  std::function<void()> User_Func0_f;
  std::function<void()> User_Func1_f;
  std::function<void()> User_Func2_f;
  std::function<void()> User_Func3_f;
  std::function<void()> User_Func4_f;
  std::function<void()> User_Func5_f;
  std::function<void()> User_Func6_f;

  // 矩阵存储空间指针
  float *xhat_data, *xhatminus_data;
  float *u_data;
  float *z_data;
  float *P_data, *Pminus_data;
  float *F_data, *FT_data;
  float *B_data;
  float *H_data, *HT_data;
  float *Q_data;
  float *R_data;
  float *K_data;
  float *S_data, *temp_matrix_data, *temp_matrix_data1, *temp_vector_data,
      *temp_vector_data1;

  uint16_t sizeof_float, sizeof_double;
  KalmanFilter(uint8_t xhatSize, uint8_t uSize, uint8_t zSize);
  void KalmanFilterMeasure();
  void KalmanFilterXhatMinusUpdate();
  void KalmanFilterPminusUpdate();
  void KalmanFilterSetK();
  void KalmanFilterXhatUpdate();
  void KalmanFilterPUpdate();
  float *KalmanFilterUpdate();
  void HKRAdjustment();
};

}  // namespace Component
