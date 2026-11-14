// u1113 – ceres::StringToNumericDiffMethodType
// Trích từ internal/ceres/types.cc, dòng 317–324 (chỉ để xem, không compile)

bool StringToNumericDiffMethodType(std::string value,
                                   NumericDiffMethodType* type) {
  UpperCase(&value);
  STRENUM(CENTRAL);
  STRENUM(FORWARD);
  STRENUM(RIDDERS);
  return false;
}
