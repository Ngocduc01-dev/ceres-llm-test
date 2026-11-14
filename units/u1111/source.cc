// u1111 – ceres::StringToLineSearchInterpolationType
// Trích từ internal/ceres/types.cc, dòng 261–268 (chỉ để xem, không compile)

bool StringToLineSearchInterpolationType(std::string value,
                                         LineSearchInterpolationType* type) {
  UpperCase(&value);
  STRENUM(BISECTION);
  STRENUM(QUADRATIC);
  STRENUM(CUBIC);
  return false;
}
