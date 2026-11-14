// u1095 – ceres::StringToDoglegType
// Trích từ internal/ceres/types.cc, dòng 190–195 (chỉ để xem, không compile)

bool StringToDoglegType(std::string value, DoglegType* type) {
  UpperCase(&value);
  STRENUM(TRADITIONAL_DOGLEG);
  STRENUM(SUBSPACE_DOGLEG);
  return false;
}
