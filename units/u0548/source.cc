// u0548 – ceres::TinySolverAutoDiffFunction::operator()
// Trích từ include/ceres/tiny_solver_autodiff_function.h, dòng 129–164 (chỉ để xem, không compile)

  bool operator()(const T* parameters, T* residuals, T* jacobian) const {
    if (jacobian == nullptr) {
      // No jacobian requested, so just directly call the cost function with
      // doubles, skipping jets and derivatives.
      return cost_functor_(parameters, residuals);
    }
    // Initialize the input jets with passed parameters.
    for (int i = 0; i < kNumParameters; ++i) {
      jet_parameters_[i].a = parameters[i];  // Scalar part.
      jet_parameters_[i].v.setZero();        // Derivative part.
      jet_parameters_[i].v[i] = T(1.0);
    }

    // Initialize the output jets such that we can detect user errors.
    for (int i = 0; i < num_residuals_; ++i) {
      jet_residuals_[i].a = kImpossibleValue;
      jet_residuals_[i].v.setConstant(kImpossibleValue);
    }

    // Execute the cost function, but with jets to find the derivative.
    if (!cost_functor_(jet_parameters_, jet_residuals_.data())) {
      return false;
    }

    // Copy the jacobian out of the derivative part of the residual jets.
    Eigen::Map<Eigen::Matrix<T, kNumResiduals, kNumParameters>> jacobian_matrix(
        jacobian, num_residuals_, kNumParameters);
    for (int r = 0; r < num_residuals_; ++r) {
      residuals[r] = jet_residuals_[r].a;
      // Note that while this looks like a fast vectorized write, in practice it
      // unfortunately thrashes the cache since the writes to the column-major
      // jacobian are strided (e.g. rows are non-contiguous).
      jacobian_matrix.row(r) = jet_residuals_[r].v;
    }
    return true;
  }
