// u0480 – ceres::internal::ParameterBlock::UpperBound
// Trích từ internal/ceres/parameter_block.h, dòng 122–125 (chỉ để xem, không compile)

  double UpperBound(int index) const {
    return (upper_bounds_ ? upper_bounds_[index]
                          : std::numeric_limits<double>::max());
  }
