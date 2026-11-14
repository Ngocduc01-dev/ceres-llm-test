// u0483 – ceres::internal::ParameterBlock::LowerBoundForParameter
// Trích từ internal/ceres/parameter_block.h, dòng 295–301 (chỉ để xem, không compile)

  double LowerBoundForParameter(int index) const {
    if (lower_bounds_.get() == nullptr) {
      return -std::numeric_limits<double>::max();
    } else {
      return lower_bounds_[index];
    }
  }
