// u1511 – ceres::Problem::SetManifold
// Trích từ internal/ceres/problem.cc, dòng 96–98 (chỉ để xem, không compile)

void Problem::SetManifold(double* values, Manifold* manifold) {
  impl_->SetManifold(values, manifold);
}
