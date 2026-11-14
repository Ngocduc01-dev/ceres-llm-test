// u0479 – ceres::internal::ParameterBlock::GetState
// Trích từ internal/ceres/parameter_block.h, dòng 104–108 (chỉ để xem, không compile)

  void GetState(double* x) const {
    if (x != state_) {
      std::copy(state_, state_ + size_, x);
    }
  }
