// u1118 – ceres::StringToLineSearchDirectionType
// Trích từ internal/ceres/types.cc, dòng 224–232 (chỉ để xem, không compile)

bool StringToLineSearchDirectionType(std::string value,
                                     LineSearchDirectionType* type) {
  UpperCase(&value);
  STRENUM(STEEPEST_DESCENT);
  STRENUM(NONLINEAR_CONJUGATE_GRADIENT);
  STRENUM(LBFGS);
  STRENUM(BFGS);
  return false;
}
