// u1253 – ceres::internal::ResidualBlock::ToString
// Trích từ internal/ceres/residual_block.h, dòng 133–135 (chỉ để xem, không compile)

  std::string ToString() const {
    return StringPrintf("{residual block; index=%d}", index_);
  }
