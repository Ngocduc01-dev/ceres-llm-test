// u0755 – ceres::LineSearchInterpolationTypeToString
// Trích từ internal/ceres/types.cc, dòng 250–259 (chỉ để xem, không compile)

const char* LineSearchInterpolationTypeToString(
    LineSearchInterpolationType type) {
  switch (type) {
    CASESTR(BISECTION);
    CASESTR(QUADRATIC);
    CASESTR(CUBIC);
    default:
      return "UNKNOWN";
  }
}
