// u0573 – ceres::TinySolverAutoDiffFunction::Initialize
// Trích từ include/ceres/tiny_solver_autodiff_function.h, dòng 197–201 (chỉ để xem, không compile)

  template <int R>
  typename std::enable_if<(R != Eigen::Dynamic), void>::type Initialize(
      const CostFunctor& /* function */) {
    num_residuals_ = kNumResiduals;
  }
