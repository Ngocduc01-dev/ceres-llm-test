// u0757 – ceres::NumericDiffMethodTypeToString
// Trích từ internal/ceres/types.cc, dòng 307–315 (chỉ để xem, không compile)

const char* NumericDiffMethodTypeToString(NumericDiffMethodType type) {
  switch (type) {
    CASESTR(CENTRAL);
    CASESTR(FORWARD);
    CASESTR(RIDDERS);
    default:
      return "UNKNOWN";
  }
}
