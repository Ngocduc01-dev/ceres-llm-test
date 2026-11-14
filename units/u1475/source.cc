// u1475 – ceres::internal::(anonymous)::IsProgramValid
// Trích từ internal/ceres/trust_region_preprocessor.cc, dòng 71–73 (chỉ để xem, không compile)

bool IsProgramValid(const Program& program, std::string* error) {
  return (program.ParameterBlocksAreFinite(error) && program.IsFeasible(error));
}
