// u0733 – ceres::MinimizerTypeToString
// Trích từ internal/ceres/types.cc, dòng 197–204 (chỉ để xem, không compile)

const char* MinimizerTypeToString(MinimizerType type) {
  switch (type) {
    CASESTR(TRUST_REGION);
    CASESTR(LINE_SEARCH);
    default:
      return "UNKNOWN";
  }
}
