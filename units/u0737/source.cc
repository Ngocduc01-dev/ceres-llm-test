// u0737 – ceres::LoggingTypeToString
// Trích từ internal/ceres/types.cc, dòng 355–362 (chỉ để xem, không compile)

const char* LoggingTypeToString(LoggingType type) {
  switch (type) {
    CASESTR(SILENT);
    CASESTR(PER_MINIMIZER_ITERATION);
    default:
      return "UNKNOWN";
  }
}
