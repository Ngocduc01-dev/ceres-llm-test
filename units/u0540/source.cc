// u0540 – ceres::internal::ParameterBlock::SetUpperBound
// Trích từ internal/ceres/parameter_block.h, dòng 190–205 (chỉ để xem, không compile)

  void SetUpperBound(int index, double upper_bound) {
    CHECK_LT(index, size_);

    if (upper_bound >= std::numeric_limits<double>::max() && !upper_bounds_) {
      return;
    }

    if (!upper_bounds_) {
      upper_bounds_ = std::make_unique<double[]>(size_);
      std::fill(upper_bounds_.get(),
                upper_bounds_.get() + size_,
                std::numeric_limits<double>::max());
    }

    upper_bounds_[index] = upper_bound;
  }
