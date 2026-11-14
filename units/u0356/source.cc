// u0356 – ceres::internal::ParameterBlock::ParameterBlock
// Trích từ internal/ceres/parameter_block.h, dòng 71–75 (chỉ để xem, không compile)

  ParameterBlock(double* user_state, int size, int index)
      : user_state_(user_state),
        size_(size),
        state_(user_state),
        index_(index) {}
