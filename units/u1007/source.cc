// u1007 – ceres::internal::LBFGS::LBFGS
// Trích từ internal/ceres/line_search_direction.cc, dòng 102–108 (chỉ để xem, không compile)

  LBFGS(const int num_parameters,
        const int max_lbfgs_rank,
        const bool use_approximate_eigenvalue_bfgs_scaling)
      : low_rank_inverse_hessian_(num_parameters,
                                  max_lbfgs_rank,
                                  use_approximate_eigenvalue_bfgs_scaling),
        is_positive_definite_(true) {}
