// u0303 – ceres::GradientProblem::NumParameters
// Trích từ internal/ceres/gradient_problem.cc, dòng 60–62 (chỉ để xem, không compile)

int GradientProblem::NumParameters() const {
  return function_->NumParameters();
}
