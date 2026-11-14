// u1125 – ceres::StringToPreconditionerType
// Trích từ internal/ceres/types.cc, dòng 91–101 (chỉ để xem, không compile)

bool StringToPreconditionerType(std::string value, PreconditionerType* type) {
  UpperCase(&value);
  STRENUM(IDENTITY);
  STRENUM(JACOBI);
  STRENUM(SCHUR_JACOBI);
  STRENUM(SCHUR_POWER_SERIES_EXPANSION);
  STRENUM(CLUSTER_JACOBI);
  STRENUM(CLUSTER_TRIDIAGONAL);
  STRENUM(SUBSET);
  return false;
}
