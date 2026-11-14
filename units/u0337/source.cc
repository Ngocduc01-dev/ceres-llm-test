// u0337 – ceres::internal::LowRankInverseHessian::LowRankInverseHessian
// Trích từ internal/ceres/low_rank_inverse_hessian.cc, dòng 75–85 (chỉ để xem, không compile)

LowRankInverseHessian::LowRankInverseHessian(
    int num_parameters,
    int max_num_corrections,
    bool use_approximate_eigenvalue_scaling)
    : num_parameters_(num_parameters),
      max_num_corrections_(max_num_corrections),
      use_approximate_eigenvalue_scaling_(use_approximate_eigenvalue_scaling),
      approximate_eigenvalue_scale_(1.0),
      delta_x_history_(num_parameters, max_num_corrections),
      delta_gradient_history_(num_parameters, max_num_corrections),
      delta_x_dot_delta_gradient_(max_num_corrections) {}
