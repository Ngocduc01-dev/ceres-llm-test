// u0712 – ceres::GradientProblem::GradientProblem
// Trích từ internal/ceres/gradient_problem.cc, dòng 39–45 (chỉ để xem, không compile)

GradientProblem::GradientProblem(FirstOrderFunction* function)
    : function_(function),
      manifold_(std::make_unique<EuclideanManifold<DYNAMIC>>(
          function_->NumParameters())),
      scratch_(new double[function_->NumParameters()]) {
  CHECK(function != nullptr);
}
