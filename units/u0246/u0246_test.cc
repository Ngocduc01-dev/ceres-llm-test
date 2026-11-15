// FILE: u0246_test.cc
#include "gtest/gtest.h"

namespace {

// Hàm callback đơn giản dùng làm loss_function_ (không kiểm tra kết quả).
void TestLossCallback(void* user_data, double sq_norm, double* rho) {
  int* counter = static_cast<int*>(user_data);
  if (counter != nullptr) {
    ++(*counter);
  }
  rho[0] = sq_norm;
  rho[1] = 1.0;
  rho[2] = 0.0;
}

}  // namespace

// P1: START -> 1 -> END
TEST(CallbackLossFunctionEvaluateTest, P1_CallsLossCallback) {
  int user_value = 42;
  CallbackLossFunction loss_function(TestLossCallback, &user_value);

  double sq_norm = 3.7;
  double rho[3] = {0.0, 0.0, 0.0};

  loss_function.Evaluate(sq_norm, rho);
}
