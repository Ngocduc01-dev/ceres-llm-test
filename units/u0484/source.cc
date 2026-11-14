// u0484 – ceres::internal::ParameterBlock::UpperBoundForParameter
// Trích từ internal/ceres/parameter_block.h, dòng 303–309 (chỉ để xem, không compile)

  double UpperBoundForParameter(int index) const {
    if (upper_bounds_.get() == nullptr) {
      return std::numeric_limits<double>::max();
    } else {
      return upper_bounds_[index];
    }
  }
