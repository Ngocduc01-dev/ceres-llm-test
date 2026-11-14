// u1473 – ceres::internal::(anonymous)::IsProgramValid
// Trích từ internal/ceres/line_search_preprocessor.cc, dòng 47–53 (chỉ để xem, không compile)

bool IsProgramValid(const Program& program, std::string* error) {
  if (program.IsBoundsConstrained()) {
    *error = "LINE_SEARCH Minimizer does not support bounds.";
    return false;
  }
  return program.ParameterBlocksAreFinite(error);
}
