// u0304 – ceres::GradientProblem::NumTangentParameters
// Trích từ internal/ceres/gradient_problem.cc, dòng 64–66 (chỉ để xem, không compile)

int GradientProblem::NumTangentParameters() const {
  return manifold_->TangentSize();
}
