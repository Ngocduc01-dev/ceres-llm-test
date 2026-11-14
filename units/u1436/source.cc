// u1436 – ceres::internal::ParameterBlock::ParameterBlock
// Trích từ internal/ceres/parameter_block.h, dòng 77–85 (chỉ để xem, không compile)

  ParameterBlock(double* user_state, int size, int index, Manifold* manifold)
      : user_state_(user_state),
        size_(size),
        state_(user_state),
        index_(index) {
    if (manifold != nullptr) {
      SetManifold(manifold);
    }
  }
