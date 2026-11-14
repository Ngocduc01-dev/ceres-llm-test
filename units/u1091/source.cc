// u1091 – ceres::internal::LBFGS::NextDirection
// Trích từ internal/ceres/line_search_direction.cc, dòng 110–137 (chỉ để xem, không compile)

  bool NextDirection(const LineSearchMinimizer::State& previous,
                     const LineSearchMinimizer::State& current,
                     Vector* search_direction) override {
    CHECK(is_positive_definite_)
        << "Ceres bug: NextDirection() called on L-BFGS after inverse Hessian "
        << "approximation has become indefinite, please contact the "
        << "developers!";

    low_rank_inverse_hessian_.Update(
        previous.search_direction * previous.step_size,
        current.gradient - previous.gradient);

    search_direction->setZero();
    low_rank_inverse_hessian_.RightMultiplyAndAccumulate(
        current.gradient.data(), search_direction->data());
    *search_direction *= -1.0;

    if (search_direction->dot(current.gradient) >= 0.0) {
      LOG(WARNING) << "Numerical failure in L-BFGS update: inverse Hessian "
                   << "approximation is not positive definite, and thus "
                   << "initial gradient for search direction is positive: "
                   << search_direction->dot(current.gradient);
      is_positive_definite_ = false;
      return false;
    }

    return true;
  }
