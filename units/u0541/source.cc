// u0541 – ceres::internal::ParameterBlock::SetLowerBound
// Trích từ internal/ceres/parameter_block.h, dòng 207–222 (chỉ để xem, không compile)

  void SetLowerBound(int index, double lower_bound) {
    CHECK_LT(index, size_);

    if (lower_bound <= -std::numeric_limits<double>::max() && !lower_bounds_) {
      return;
    }

    if (!lower_bounds_) {
      lower_bounds_ = std::make_unique<double[]>(size_);
      std::fill(lower_bounds_.get(),
                lower_bounds_.get() + size_,
                -std::numeric_limits<double>::max());
    }

    lower_bounds_[index] = lower_bound;
  }
