// u1093 – ceres::StringToLinearSolverOrderingType
// Trích từ internal/ceres/types.cc, dòng 136–142 (chỉ để xem, không compile)

bool StringToLinearSolverOrderingType(std::string value,
                                      LinearSolverOrderingType* type) {
  UpperCase(&value);
  STRENUM(AMD);
  STRENUM(NESDIS);
  return false;
}
