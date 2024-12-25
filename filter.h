/*
  各类滤波器。
*/

#pragma once

#include <component.hpp>

namespace Component {
/* 一阶数字低通滤波器 */
class LowPassFilter {
 public:
  LowPassFilter(void) : LowPassFilter(1.f, 0) {}
  LowPassFilter(float k) : LowPassFilter(k, 0) {}
  LowPassFilter(float k, float init) : k_(k), output_(init) {}

  float update(float input);
  inline void setK(float k) { k_ = k; }
  inline void reset(float val = 0) {
    input_ = val;
    output_ = val;
  }

 private:
  float k_;
  float input_, output_;
};
/* 二阶巴特沃斯低通滤波器 */
class LowPassFilter2p {
 public:
  LowPassFilter2p(float sample_freq, float cutoff_freq);

  float Apply(float sample);

  float Reset(float sample);

 private:
  float cutoff_freq_; /* 截止频率 */

  float a1_;
  float a2_;

  float b0_;
  float b1_;
  float b2_;

  float delay_element_1_;
  float delay_element_2_;
};
}  // namespace Component
