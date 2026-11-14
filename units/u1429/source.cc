// u1429 – ceres::Problem::HasManifold
// Trích từ internal/ceres/problem.cc, dòng 104–106 (chỉ để xem, không compile)

bool Problem::HasManifold(const double* values) const {
  return impl_->HasManifold(values);
}
