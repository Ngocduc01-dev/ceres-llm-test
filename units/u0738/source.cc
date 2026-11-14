// u0738 – ceres::DumpFormatTypeToString
// Trích từ internal/ceres/types.cc, dòng 371–378 (chỉ để xem, không compile)

const char* DumpFormatTypeToString(DumpFormatType type) {
  switch (type) {
    CASESTR(CONSOLE);
    CASESTR(TEXTFILE);
    default:
      return "UNKNOWN";
  }
}
