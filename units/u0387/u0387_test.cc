// FILE: u0387_test.cc
#include "gtest/gtest.h"
#include "ceres/preprocessor.h"

namespace ceres {
namespace internal {

namespace {

// Lớp con tối thiểu để có thể tạo object (Preprocessor có hàm thuần ảo).
class TestPreprocessor : public Preprocessor {
 public:
  bool Preprocess(const Solver::Options& /*options*/,
                  ProblemImpl* /*problem*/,
                  PreprocessedProblem* /*pp*/) override {
    return true;
  }
};

}  // namespace

// P1: START -> END (destructor không có nhánh)
TEST(PreprocessorDestructorTest, DestroyThroughBasePointer) {
  Preprocessor* preprocessor = new TestPreprocessor();
  delete preprocessor;  // gọi ~TestPreprocessor() rồi ~Preprocessor() đúng một lần
}

}  // namespace internal
}  // namespace ceres
