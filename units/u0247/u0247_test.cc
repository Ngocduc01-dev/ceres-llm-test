// FILE: u0247_test.cc
#include "gtest/gtest.h"
#include "ceres/callbacks.h"

namespace ceres {
namespace internal {

// Path P1: START -> END (không có điểm rẽ nhánh)
TEST(StateUpdatingCallbackDestructorTest, P1_StartToEnd) {
  double parameters[1] = {0.5};
  StateUpdatingCallback* callback =
      new StateUpdatingCallback(nullptr, parameters);
  delete callback;  // gọi ~StateUpdatingCallback() một lần
}

}  // namespace internal
}  // namespace ceres
