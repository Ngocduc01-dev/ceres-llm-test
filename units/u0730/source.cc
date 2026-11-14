// u0730 – ceres::LinearSolverOrderingTypeToString
// Trích từ internal/ceres/types.cc, dòng 127–134 (chỉ để xem, không compile)

const char* LinearSolverOrderingTypeToString(LinearSolverOrderingType type) {
  switch (type) {
    CASESTR(AMD);
    CASESTR(NESDIS);
    default:
      return "UNKNOWN";
  }
}
