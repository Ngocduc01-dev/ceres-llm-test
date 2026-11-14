// u0936 – ceres::GradientProblem::GradientProblem
// Trích từ internal/ceres/gradient_problem.cc, dòng 47–58 (chỉ để xem, không compile)

GradientProblem::GradientProblem(FirstOrderFunction* function,
                                 Manifold* manifold)
    : function_(function), scratch_(new double[function_->NumParameters()]) {
  CHECK(function != nullptr);
  if (manifold != nullptr) {
    manifold_.reset(manifold);
  } else {
    manifold_ = std::make_unique<EuclideanManifold<DYNAMIC>>(
        function_->NumParameters());
  }
  CHECK_EQ(function_->NumParameters(), manifold_->AmbientSize());
}
