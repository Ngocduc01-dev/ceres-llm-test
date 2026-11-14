// u0468 – ceres::internal::BFGS::BFGS
// Trích từ internal/ceres/line_search_direction.cc, dòng 146–162 (chỉ để xem, không compile)

  BFGS(const int num_parameters, const bool use_approximate_eigenvalue_scaling)
      : num_parameters_(num_parameters),
        use_approximate_eigenvalue_scaling_(use_approximate_eigenvalue_scaling),
        initialized_(false),
        is_positive_definite_(true) {
    if (num_parameters_ >= 1000) {
      LOG(WARNING) << "BFGS line search being created with: " << num_parameters_
                   << " parameters, this will allocate a dense approximate "
                   << "inverse Hessian of size: " << num_parameters_ << " x "
                   << num_parameters_
                   << ", consider using the L-BFGS memory-efficient line "
                   << "search direction instead.";
    }
    // Construct inverse_hessian_ after logging warning about size s.t. if the
    // allocation crashes us, the log will highlight what the issue likely was.
    inverse_hessian_ = Matrix::Identity(num_parameters, num_parameters);
  }
