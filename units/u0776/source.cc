// u0776 – ceres::LinearSolverTypeToString
// Trích từ internal/ceres/types.cc, dòng 51–63 (chỉ để xem, không compile)

const char* LinearSolverTypeToString(LinearSolverType type) {
  switch (type) {
    CASESTR(DENSE_NORMAL_CHOLESKY);
    CASESTR(DENSE_QR);
    CASESTR(SPARSE_NORMAL_CHOLESKY);
    CASESTR(DENSE_SCHUR);
    CASESTR(SPARSE_SCHUR);
    CASESTR(ITERATIVE_SCHUR);
    CASESTR(CGNR);
    default:
      return "UNKNOWN";
  }
}
