// u0766 – ceres::LineSearchDirectionTypeToString
// Trích từ internal/ceres/types.cc, dòng 213–222 (chỉ để xem, không compile)

const char* LineSearchDirectionTypeToString(LineSearchDirectionType type) {
  switch (type) {
    CASESTR(STEEPEST_DESCENT);
    CASESTR(NONLINEAR_CONJUGATE_GRADIENT);
    CASESTR(LBFGS);
    CASESTR(BFGS);
    default:
      return "UNKNOWN";
  }
}
