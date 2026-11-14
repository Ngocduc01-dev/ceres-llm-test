// u1110 – ceres::StringToDenseLinearAlgebraLibraryType
// Trích từ internal/ceres/types.cc, dòng 155–162 (chỉ để xem, không compile)

bool StringToDenseLinearAlgebraLibraryType(
    std::string value, DenseLinearAlgebraLibraryType* type) {
  UpperCase(&value);
  STRENUM(EIGEN);
  STRENUM(LAPACK);
  STRENUM(CUDA);
  return false;
}
