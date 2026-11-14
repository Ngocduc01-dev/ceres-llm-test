// u0719 – ceres::TinySolver::Update
// Trích từ include/ceres/tiny_solver.h, dòng 190–218 (chỉ để xem, không compile)

  bool Update(const Function& function, const Parameters& x) {
    if (!function(x.data(), residuals_.data(), jacobian_.data())) {
      return false;
    }

    residuals_ = -residuals_;

    // On the first iteration, compute a diagonal (Jacobi) scaling
    // matrix, which we store as a vector.
    if (summary.iterations == 0) {
      // jacobi_scaling = 1 / (1 + diagonal(J'J))
      //
      // 1 is added to the denominator to regularize small diagonal
      // entries.
      jacobi_scaling_ = 1.0 / (1.0 + jacobian_.colwise().norm().array());
    }

    // This explicitly computes the normal equations, which is numerically
    // unstable. Nevertheless, it is often good enough and is fast.
    //
    // TODO(sameeragarwal): Refactor this to allow for DenseQR
    // factorization.
    jacobian_ = jacobian_ * jacobi_scaling_.asDiagonal();
    jtj_ = jacobian_.transpose() * jacobian_;
    g_ = jacobian_.transpose() * residuals_;
    summary.gradient_max_norm = g_.array().abs().maxCoeff();
    cost_ = residuals_.squaredNorm() / 2;
    return true;
  }
