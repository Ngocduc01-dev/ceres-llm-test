// u0572 – ceres::TinySolverAutoDiffFunction::Initialize
// Trích từ include/ceres/tiny_solver_autodiff_function.h, dòng 189–194 (chỉ để xem, không compile)

  template <int R>
  typename std::enable_if<(R == Eigen::Dynamic), void>::type Initialize(
      const CostFunctor& function) {
    jet_residuals_.resize(function.NumResiduals());
    num_residuals_ = function.NumResiduals();
  }
