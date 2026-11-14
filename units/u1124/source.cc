// u1124 – ceres::StringToLinearSolverType
// Trích từ internal/ceres/types.cc, dòng 65–75 (chỉ để xem, không compile)

bool StringToLinearSolverType(std::string value, LinearSolverType* type) {
  UpperCase(&value);
  STRENUM(DENSE_NORMAL_CHOLESKY);
  STRENUM(DENSE_QR);
  STRENUM(SPARSE_NORMAL_CHOLESKY);
  STRENUM(DENSE_SCHUR);
  STRENUM(SPARSE_SCHUR);
  STRENUM(ITERATIVE_SCHUR);
  STRENUM(CGNR);
  return false;
}
