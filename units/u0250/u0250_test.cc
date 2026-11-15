// FILE: u0250_test.cc
#include "gtest/gtest.h"
#include "ceres/callbacks.h"

namespace ceres {
namespace internal {

// Path P1: START -> END (không có điểm rẽ nhánh)
TEST(LoggingCallbackDestructorTest, P1_DestroyObject) {
  // Object được cấp phát động; delete sẽ gọi ~LoggingCallback() đúng một lần.
  LoggingCallback* callback =
      new LoggingCallback(TRUST_REGION, /*log_to_stdout=*/false);
  delete callback;
}

}  // namespace internal
}  // namespace ceres
