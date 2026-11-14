// u1096 – ceres::StringToMinimizerType
// Trích từ internal/ceres/types.cc, dòng 206–211 (chỉ để xem, không compile)

bool StringToMinimizerType(std::string value, MinimizerType* type) {
  UpperCase(&value);
  STRENUM(TRUST_REGION);
  STRENUM(LINE_SEARCH);
  return false;
}
