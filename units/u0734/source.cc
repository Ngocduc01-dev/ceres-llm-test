// u0734 – ceres::LineSearchTypeToString
// Trích từ internal/ceres/types.cc, dòng 234–241 (chỉ để xem, không compile)

const char* LineSearchTypeToString(LineSearchType type) {
  switch (type) {
    CASESTR(ARMIJO);
    CASESTR(WOLFE);
    default:
      return "UNKNOWN";
  }
}
