// u1331 – ceres::Problem::GetManifold
// Trích từ internal/ceres/problem.cc, dòng 100–102 (chỉ để xem, không compile)

const Manifold* Problem::GetManifold(const double* values) const {
  return impl_->GetManifold(values);
}
