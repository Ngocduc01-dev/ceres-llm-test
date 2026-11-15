// FILE: u0245_test.cc
#include "gtest/gtest.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(CallbackLossFunctionConstructorTest, P1_ConstructWithNullCallbackAndUserData) {
  int data = 3;
  ceres_loss_function_t loss_function = nullptr;
  void* user_data = &data;

  CallbackLossFunction loss(loss_function, user_data);
}
