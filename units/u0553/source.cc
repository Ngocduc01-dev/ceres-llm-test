// u0553 – ceres::internal::ParameterBlock::Plus
// Trích từ internal/ceres/parameter_block.h, dòng 227–251 (chỉ để xem, không compile)

  bool Plus(const double* x, const double* delta, double* x_plus_delta) {
    if (manifold_ != nullptr) {
      if (!manifold_->Plus(x, delta, x_plus_delta)) {
        return false;
      }
    } else {
      VectorRef(x_plus_delta, size_) =
          ConstVectorRef(x, size_) + ConstVectorRef(delta, size_);
    }

    // Project onto the box constraints.
    if (lower_bounds_.get() != nullptr) {
      for (int i = 0; i < size_; ++i) {
        x_plus_delta[i] = std::max(x_plus_delta[i], lower_bounds_[i]);
      }
    }

    if (upper_bounds_.get() != nullptr) {
      for (int i = 0; i < size_; ++i) {
        x_plus_delta[i] = std::min(x_plus_delta[i], upper_bounds_[i]);
      }
    }

    return true;
  }
