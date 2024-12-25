#include "comp_kalfilter.hpp"

using namespace Component;

KalmanFilter::KalmanFilter(uint8_t xhatSize, uint8_t uSize, uint8_t zSize)
    : xhatSize(xhatSize),
      uSize(uSize),
      zSize(zSize),
      MeasurementValidNum(0),
      MeasurementMap(
          static_cast<uint8_t *>(user_malloc(sizeof(uint8_t) * zSize))),
      temp(static_cast<uint8_t *>(user_malloc(sizeof(uint8_t) * zSize))),
      sizeof_float(sizeof(float)),
      sizeof_double(sizeof(double)) {
  // measurement flags
  memset(this->MeasurementMap, 0, sizeof(uint8_t) * zSize);
  this->MeasurementDegree =
      static_cast<float *>(user_malloc(sizeof_float * zSize));
  memset(this->MeasurementDegree, 0, sizeof_float * zSize);
  this->MatR_DiagonalElements =
      static_cast<float *>(user_malloc(sizeof_float * zSize));
  memset(this->MatR_DiagonalElements, 0, sizeof_float * zSize);
  this->StateMinVariance =
      static_cast<float *>(user_malloc(sizeof_float * xhatSize));
  memset(this->StateMinVariance, 0, sizeof_float * xhatSize);

  memset(this->temp, 0, sizeof(uint8_t) * zSize);

  // filter data
  this->FilteredValue =
      static_cast<float *>(user_malloc(sizeof_float * xhatSize));
  memset(this->FilteredValue, 0, sizeof_float * xhatSize);
  this->MeasuredVector =
      static_cast<float *>(user_malloc(sizeof_float * zSize));
  memset(this->MeasuredVector, 0, sizeof_float * zSize);
  this->ControlVector = static_cast<float *>(user_malloc(sizeof_float * uSize));
  memset(this->ControlVector, 0, sizeof_float * uSize);

  // xhat x(k|k)
  this->xhat_data = static_cast<float *>(user_malloc(sizeof_float * xhatSize));
  memset(this->xhat_data, 0, sizeof_float * xhatSize);
  Matrix_Init(&this->xhat, this->xhatSize, 1, this->xhat_data);

  // xhatminus x(k|k-1)
  this->xhatminus_data =
      static_cast<float *>(user_malloc(sizeof_float * xhatSize));
  memset(this->xhatminus_data, 0, sizeof_float * xhatSize);
  Matrix_Init(&this->xhatminus, this->xhatSize, 1, this->xhatminus_data);

  if (uSize != 0) {
    // control vector u
    this->u_data = static_cast<float *>(user_malloc(sizeof_float * uSize));
    memset(this->u_data, 0, sizeof_float * uSize);
    Matrix_Init(&this->u, this->uSize, 1, this->u_data);
  }

  // measurement vector z
  this->z_data = static_cast<float *>(user_malloc(sizeof_float * zSize));
  memset(this->z_data, 0, sizeof_float * zSize);
  Matrix_Init(&this->z, this->zSize, 1, this->z_data);

  // covariance matrix P(k|k)
  this->P_data =
      static_cast<float *>(user_malloc(sizeof_float * xhatSize * xhatSize));
  ;
  memset(this->P_data, 0, sizeof_float * xhatSize * xhatSize);
  Matrix_Init(&this->P, this->xhatSize, this->xhatSize, this->P_data);

  // create covariance matrix P(k|k-1)
  this->Pminus_data =
      static_cast<float *>(user_malloc(sizeof_float * xhatSize * xhatSize));
  ;
  memset(this->Pminus_data, 0, sizeof_float * xhatSize * xhatSize);
  Matrix_Init(&this->Pminus, this->xhatSize, this->xhatSize, this->Pminus_data);

  // state transition matrix F FT
  this->F_data =
      static_cast<float *>(user_malloc(sizeof_float * xhatSize * xhatSize));
  ;
  this->FT_data =
      static_cast<float *>(user_malloc(sizeof_float * xhatSize * xhatSize));
  ;
  memset(this->F_data, 0, sizeof_float * xhatSize * xhatSize);
  memset(this->FT_data, 0, sizeof_float * xhatSize * xhatSize);
  Matrix_Init(&this->F, this->xhatSize, this->xhatSize, this->F_data);
  Matrix_Init(&this->FT, this->xhatSize, this->xhatSize, this->FT_data);

  if (uSize != 0) {
    // control matrix B
    this->B_data =
        static_cast<float *>(user_malloc(sizeof_float * xhatSize * uSize));
    ;
    memset(this->B_data, 0, sizeof_float * xhatSize * uSize);
    Matrix_Init(&this->B, this->xhatSize, this->uSize, this->B_data);
  }

  // measurement matrix H
  this->H_data =
      static_cast<float *>(user_malloc(sizeof_float * zSize * xhatSize));
  ;
  this->HT_data =
      static_cast<float *>(user_malloc(sizeof_float * xhatSize * zSize));
  ;
  memset(this->H_data, 0, sizeof_float * zSize * xhatSize);
  memset(this->HT_data, 0, sizeof_float * xhatSize * zSize);
  Matrix_Init(&this->H, this->zSize, this->xhatSize, this->H_data);
  Matrix_Init(&this->HT, this->xhatSize, this->zSize, this->HT_data);

  // process noise covariance matrix Q
  this->Q_data =
      static_cast<float *>(user_malloc(sizeof_float * xhatSize * xhatSize));
  ;
  memset(this->Q_data, 0, sizeof_float * xhatSize * xhatSize);
  Matrix_Init(&this->Q, this->xhatSize, this->xhatSize, this->Q_data);

  // measurement noise covariance matrix R
  this->R_data =
      static_cast<float *>(user_malloc(sizeof_float * zSize * zSize));
  ;
  memset(this->R_data, 0, sizeof_float * zSize * zSize);
  Matrix_Init(&this->R, this->zSize, this->zSize, this->R_data);

  // kalman gain K
  this->K_data =
      static_cast<float *>(user_malloc(sizeof_float * xhatSize * zSize));
  ;
  memset(this->K_data, 0, sizeof_float * xhatSize * zSize);
  Matrix_Init(&this->K, this->xhatSize, this->zSize, this->K_data);

  this->S_data = static_cast<float *>(
      user_malloc(sizeof_float * this->xhatSize * this->xhatSize));
  ;
  this->temp_matrix_data = static_cast<float *>(
      user_malloc(sizeof_float * this->xhatSize * this->xhatSize));
  ;
  this->temp_matrix_data1 = static_cast<float *>(
      user_malloc(sizeof_float * this->xhatSize * this->xhatSize));
  ;
  this->temp_vector_data =
      static_cast<float *>(user_malloc(sizeof_float * this->xhatSize));
  ;
  this->temp_vector_data1 =
      static_cast<float *>(user_malloc(sizeof_float * this->xhatSize));
  ;
  Matrix_Init(&this->S, this->xhatSize, this->xhatSize, this->S_data);
  Matrix_Init(&this->temp_matrix, this->xhatSize, this->xhatSize,
              this->temp_matrix_data);
  Matrix_Init(&this->temp_matrix1, this->xhatSize, this->xhatSize,
              this->temp_matrix_data1);
  Matrix_Init(&this->temp_vector, this->xhatSize, 1, this->temp_vector_data);
  Matrix_Init(&this->temp_vector1, this->xhatSize, 1, this->temp_vector_data1);

  this->SkipEq1 = 0;
  this->SkipEq2 = 0;
  this->SkipEq3 = 0;
  this->SkipEq4 = 0;
  this->SkipEq5 = 0;
}

void KalmanFilter::KalmanFilterMeasure() {  // 矩阵H K R根据量测情况自动调整
  // matrix H K R auto adjustment
  if (this->UseAutoAdjustment != 0) {
    KalmanFilter::HKRAdjustment();
  } else {
    memcpy(this->z_data, this->MeasuredVector, sizeof_float * this->zSize);
    memset(this->MeasuredVector, 0, sizeof_float * this->zSize);
  }

  memcpy(this->u_data, this->ControlVector, sizeof_float * this->uSize);
}
void KalmanFilter::KalmanFilterXhatMinusUpdate() {
  if (!this->SkipEq1) {
    if (this->uSize > 0) {
      this->temp_vector.numRows = this->xhatSize;
      this->temp_vector.numCols = 1;
      this->MatStatus =
          Matrix_Multiply(&this->F, &this->xhat, &this->temp_vector);
      this->temp_vector1.numRows = this->xhatSize;
      this->temp_vector1.numCols = 1;
      this->MatStatus =
          Matrix_Multiply(&this->B, &this->u, &this->temp_vector1);
      this->MatStatus =
          Matrix_Add(&this->temp_vector, &this->temp_vector1, &this->xhatminus);
    } else {
      this->MatStatus =
          Matrix_Multiply(&this->F, &this->xhat, &this->xhatminus);
    }
  }
}

void KalmanFilter::KalmanFilterPminusUpdate() {
  if (!this->SkipEq2) {
    this->MatStatus = Matrix_Transpose(&this->F, &this->FT);
    this->MatStatus = Matrix_Multiply(&this->F, &this->P, &this->Pminus);
    this->temp_matrix.numRows = this->Pminus.numRows;
    this->temp_matrix.numCols = this->FT.numCols;
    this->MatStatus =
        Matrix_Multiply(&this->Pminus, &this->FT,
                        &this->temp_matrix);  // temp_matrix = F P(k-1) FT
    this->MatStatus = Matrix_Add(&this->temp_matrix, &this->Q, &this->Pminus);
  }
}
void KalmanFilter::KalmanFilterSetK() {
  if (!this->SkipEq3) {
    this->MatStatus = Matrix_Transpose(&this->H, &this->HT);  // z|x => x|z
    this->temp_matrix.numRows = this->H.numRows;
    this->temp_matrix.numCols = this->Pminus.numCols;
    this->MatStatus =
        Matrix_Multiply(&this->H, &this->Pminus,
                        &this->temp_matrix);  // temp_matrix = H·P'(k)
    this->temp_matrix1.numRows = this->temp_matrix.numRows;
    this->temp_matrix1.numCols = this->HT.numCols;
    this->MatStatus =
        Matrix_Multiply(&this->temp_matrix, &this->HT,
                        &this->temp_matrix1);  // temp_matrix1 = H·P'(k)·HT
    this->S.numRows = this->R.numRows;
    this->S.numCols = this->R.numCols;
    this->MatStatus = Matrix_Add(&this->temp_matrix1, &this->R,
                                 &this->S);  // S = H P'(k) HT + R
    this->MatStatus = Matrix_Inverse(
        &this->S, &this->temp_matrix1);  // temp_matrix1 = inv(H·P'(k)·HT + R)
    this->temp_matrix.numRows = this->Pminus.numRows;
    this->temp_matrix.numCols = this->HT.numCols;
    this->MatStatus =
        Matrix_Multiply(&this->Pminus, &this->HT,
                        &this->temp_matrix);  // temp_matrix = P'(k)·HT
    this->MatStatus =
        Matrix_Multiply(&this->temp_matrix, &this->temp_matrix1, &this->K);
  }
}
void KalmanFilter::KalmanFilterXhatUpdate() {
  if (!this->SkipEq4) {
    this->temp_vector.numRows = this->H.numRows;
    this->temp_vector.numCols = 1;
    this->MatStatus =
        Matrix_Multiply(&this->H, &this->xhatminus,
                        &this->temp_vector);  // temp_vector = H xhat'(k)
    this->temp_vector1.numRows = this->z.numRows;
    this->temp_vector1.numCols = 1;
    this->MatStatus = Matrix_Subtract(
        &this->z, &this->temp_vector,
        &this->temp_vector1);  // temp_vector1 = z(k) - H·xhat'(k)
    this->temp_vector.numRows = this->K.numRows;
    this->temp_vector.numCols = 1;
    this->MatStatus = Matrix_Multiply(
        &this->K, &this->temp_vector1,
        &this->temp_vector);  // temp_vector = K(k)·(z(k) - H·xhat'(k))
    this->MatStatus =
        Matrix_Add(&this->xhatminus, &this->temp_vector, &this->xhat);
  }
}
void KalmanFilter::KalmanFilterPUpdate() {
  if (!this->SkipEq5) {
    this->temp_matrix.numRows = this->K.numRows;
    this->temp_matrix.numCols = this->H.numCols;
    this->temp_matrix1.numRows = this->temp_matrix.numRows;
    this->temp_matrix1.numCols = this->Pminus.numCols;
    this->MatStatus =
        Matrix_Multiply(&this->K, &this->H,
                        &this->temp_matrix);  // temp_matrix = K(k)·H
    this->MatStatus =
        Matrix_Multiply(&this->temp_matrix, &this->Pminus,
                        &this->temp_matrix1);  // temp_matrix1 = K(k)·H·P'(k)
    this->MatStatus =
        Matrix_Subtract(&this->Pminus, &this->temp_matrix1, &this->P);
  }
}

/**
 * @brief
 * 执行卡尔曼滤波黄金五式,提供了用户定义函数,可以替代五个中的任意一个环节,方便自行扩展为EKF/UKF/ESKF/AUKF等
 *
 * @return float* 返回滤波值
 */
float *KalmanFilter::KalmanFilterUpdate() {
  // 0. 获取量测信息
  KalmanFilterMeasure();
  if (this->User_Func0_f != NULL) {
    this->User_Func0_f();
  }

  // 先验估计
  // 1. xhat'(k)= A·xhat(k-1) + B·u
  KalmanFilterXhatMinusUpdate();
  if (this->User_Func1_f != NULL) {
    this->User_Func1_f();
  }

  // 预测更新
  // 2. P'(k) = A·P(k-1)·AT + Q
  KalmanFilterPminusUpdate();
  if (this->User_Func2_f != NULL) {
    this->User_Func2_f();
  }

  if (this->MeasurementValidNum != 0 || this->UseAutoAdjustment == 0) {
    // 量测更新
    // 3. K(k) = P'(k)·HT / (H·P'(k)·HT + R)
    KalmanFilterSetK();

    if (this->User_Func3_f != NULL) {
      this->User_Func3_f();
    }

    // 融合
    // 4. xhat(k) = xhat'(k) + K(k)·(z(k) - H·xhat'(k))
    KalmanFilterXhatUpdate();

    if (this->User_Func4_f != NULL) {
      this->User_Func4_f();
    }

    // 修正方差
    // 5. P(k) = (1-K(k)·H)·P'(k) ==> P(k) = P'(k)-K(k)·H·P'(k)
    KalmanFilterPUpdate();
  } else {
    // 无有效量测,仅预测
    // xhat(k) = xhat'(k)
    // P(k) = P'(k)
    memcpy(this->xhat_data, this->xhatminus_data,
           sizeof_float * this->xhatSize);
    memcpy(this->P_data, this->Pminus_data,
           sizeof_float * this->xhatSize * this->xhatSize);
  }

  // 自定义函数,可以提供后处理等
  if (this->User_Func5_f != NULL) {
    this->User_Func5_f();
  }

  // 避免滤波器过度收敛
  // suppress filter excessive convergence
  for (uint8_t i = 0; i < this->xhatSize; ++i) {
    if (this->P_data[i * this->xhatSize + i] < this->StateMinVariance[i]) {
      this->P_data[i * this->xhatSize + i] = this->StateMinVariance[i];
    }
  }

  memcpy(this->FilteredValue, this->xhat_data, sizeof_float * this->xhatSize);

  if (this->User_Func6_f != NULL) {
    this->User_Func6_f();
  }

  return this->FilteredValue;
}

void KalmanFilter::HKRAdjustment() {
  this->MeasurementValidNum = 0;

  memcpy(this->z_data, this->MeasuredVector, sizeof_float * this->zSize);
  memset(this->MeasuredVector, 0, sizeof_float * this->zSize);

  // 识别量测数据有效性并调整矩阵H R K
  // recognize measurement validity and adjust matrices H R K
  memset(this->R_data, 0, sizeof_float * this->zSize * this->zSize);
  memset(this->H_data, 0, sizeof_float * this->xhatSize * this->zSize);
  for (uint8_t i = 0; i < this->zSize; ++i) {
    if (this->z_data[i] != 0) {
      // 重构向量z
      // rebuild vector z
      this->z_data[this->MeasurementValidNum] = this->z_data[i];
      this->temp[this->MeasurementValidNum] = i;
      // 重构矩阵H
      // rebuild matrix H
      this->H_data[this->xhatSize * this->MeasurementValidNum +
                   this->MeasurementMap[i] - 1] = this->MeasurementDegree[i];
      this->MeasurementValidNum++;
    }
  }
  for (uint8_t i = 0; i < this->MeasurementValidNum; ++i) {
    // 重构矩阵R
    // rebuild matrix R
    this->R_data[i * this->MeasurementValidNum + i] =
        this->MatR_DiagonalElements[this->temp[i]];
  }

  // 调整矩阵维数
  // adjust the dimensions of system matrices
  this->H.numRows = this->MeasurementValidNum;
  this->H.numCols = this->xhatSize;
  this->HT.numRows = this->xhatSize;
  this->HT.numCols = this->MeasurementValidNum;
  this->R.numRows = this->MeasurementValidNum;
  this->R.numCols = this->MeasurementValidNum;
  this->K.numRows = this->xhatSize;
  this->K.numCols = this->MeasurementValidNum;
  this->z.numRows = this->MeasurementValidNum;
}
