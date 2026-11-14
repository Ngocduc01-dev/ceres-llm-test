// u0754 – ceres::DenseLinearAlgebraLibraryTypeToString
// Trích từ internal/ceres/types.cc, dòng 144–153 (chỉ để xem, không compile)

const char* DenseLinearAlgebraLibraryTypeToString(
    DenseLinearAlgebraLibraryType type) {
  switch (type) {
    CASESTR(EIGEN);
    CASESTR(LAPACK);
    CASESTR(CUDA);
    default:
      return "UNKNOWN";
  }
}
