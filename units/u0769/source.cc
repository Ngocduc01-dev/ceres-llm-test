// u0769 – ceres::SparseLinearAlgebraLibraryTypeToString
// Trích từ internal/ceres/types.cc, dòng 103–114 (chỉ để xem, không compile)

const char* SparseLinearAlgebraLibraryTypeToString(
    SparseLinearAlgebraLibraryType type) {
  switch (type) {
    CASESTR(SUITE_SPARSE);
    CASESTR(EIGEN_SPARSE);
    CASESTR(ACCELERATE_SPARSE);
    CASESTR(CUDA_SPARSE);
    CASESTR(NO_SPARSE);
    default:
      return "UNKNOWN";
  }
}
