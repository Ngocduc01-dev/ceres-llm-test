// u0777 – ceres::PreconditionerTypeToString
// Trích từ internal/ceres/types.cc, dòng 77–89 (chỉ để xem, không compile)

const char* PreconditionerTypeToString(PreconditionerType type) {
  switch (type) {
    CASESTR(IDENTITY);
    CASESTR(JACOBI);
    CASESTR(SCHUR_JACOBI);
    CASESTR(SCHUR_POWER_SERIES_EXPANSION);
    CASESTR(CLUSTER_JACOBI);
    CASESTR(CLUSTER_TRIDIAGONAL);
    CASESTR(SUBSET);
    default:
      return "UNKNOWN";
  }
}
