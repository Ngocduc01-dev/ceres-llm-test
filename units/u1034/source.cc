// u1034 – ceres::internal::ParameterBlock::IsConstant
// Trích từ internal/ceres/parameter_block.h, dòng 120–120 (chỉ để xem, không compile)

  bool IsConstant() const { return (is_set_constant_ || TangentSize() == 0); }
