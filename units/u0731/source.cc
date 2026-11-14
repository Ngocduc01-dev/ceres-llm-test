// u0731 – ceres::TrustRegionStrategyTypeToString
// Trích từ internal/ceres/types.cc, dòng 164–171 (chỉ để xem, không compile)

const char* TrustRegionStrategyTypeToString(TrustRegionStrategyType type) {
  switch (type) {
    CASESTR(LEVENBERG_MARQUARDT);
    CASESTR(DOGLEG);
    default:
      return "UNKNOWN";
  }
}
