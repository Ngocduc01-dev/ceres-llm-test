// u1112 – ceres::StringToNonlinearConjugateGradientType
// Trích từ internal/ceres/types.cc, dòng 281–288 (chỉ để xem, không compile)

bool StringToNonlinearConjugateGradientType(
    std::string value, NonlinearConjugateGradientType* type) {
  UpperCase(&value);
  STRENUM(FLETCHER_REEVES);
  STRENUM(POLAK_RIBIERE);
  STRENUM(HESTENES_STIEFEL);
  return false;
}
