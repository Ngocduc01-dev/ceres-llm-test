// u1097 – ceres::StringToLineSearchType
// Trích từ internal/ceres/types.cc, dòng 243–248 (chỉ để xem, không compile)

bool StringToLineSearchType(std::string value, LineSearchType* type) {
  UpperCase(&value);
  STRENUM(ARMIJO);
  STRENUM(WOLFE);
  return false;
}
