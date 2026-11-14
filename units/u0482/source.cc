// u0482 – ceres::internal::ParameterBlock::TangentSize
// Trích từ internal/ceres/parameter_block.h, dòng 154–156 (chỉ để xem, không compile)

  int TangentSize() const {
    return (manifold_ == nullptr) ? size_ : manifold_->TangentSize();
  }
