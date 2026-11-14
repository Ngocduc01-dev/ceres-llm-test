// u0481 – ceres::internal::ParameterBlock::LowerBound
// Trích từ internal/ceres/parameter_block.h, dòng 127–130 (chỉ để xem, không compile)

  double LowerBound(int index) const {
    return (lower_bounds_ ? lower_bounds_[index]
                          : -std::numeric_limits<double>::max());
  }
