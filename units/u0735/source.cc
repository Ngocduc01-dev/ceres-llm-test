// u0735 – ceres::CovarianceAlgorithmTypeToString
// Trích từ internal/ceres/types.cc, dòng 290–297 (chỉ để xem, không compile)

const char* CovarianceAlgorithmTypeToString(CovarianceAlgorithmType type) {
  switch (type) {
    CASESTR(DENSE_SVD);
    CASESTR(SPARSE_QR);
    default:
      return "UNKNOWN";
  }
}
