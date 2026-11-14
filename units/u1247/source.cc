// u1247 – ceres::internal::ParameterBlock::ToString
// Trích từ internal/ceres/parameter_block.h, dòng 253–266 (chỉ để xem, không compile)

  std::string ToString() const {
    return StringPrintf(
        "{ this=%p, user_state=%p, state=%p, size=%d, "
        "constant=%d, index=%d, state_offset=%d, "
        "delta_offset=%d }",
        this,
        user_state_,
        state_,
        size_,
        is_set_constant_,
        index_,
        state_offset_,
        delta_offset_);
  }
