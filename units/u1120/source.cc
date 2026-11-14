// u1120 – ceres::StringToSparseLinearAlgebraLibraryType
// Trích từ internal/ceres/types.cc, dòng 116–125 (chỉ để xem, không compile)

bool StringToSparseLinearAlgebraLibraryType(
    std::string value, SparseLinearAlgebraLibraryType* type) {
  UpperCase(&value);
  STRENUM(SUITE_SPARSE);
  STRENUM(EIGEN_SPARSE);
  STRENUM(ACCELERATE_SPARSE);
  STRENUM(CUDA_SPARSE);
  STRENUM(NO_SPARSE);
  return false;
}
