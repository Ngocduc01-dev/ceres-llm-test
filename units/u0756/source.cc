// u0756 – ceres::NonlinearConjugateGradientTypeToString
// Trích từ internal/ceres/types.cc, dòng 270–279 (chỉ để xem, không compile)

const char* NonlinearConjugateGradientTypeToString(
    NonlinearConjugateGradientType type) {
  switch (type) {
    CASESTR(FLETCHER_REEVES);
    CASESTR(POLAK_RIBIERE);
    CASESTR(HESTENES_STIEFEL);
    default:
      return "UNKNOWN";
  }
}
