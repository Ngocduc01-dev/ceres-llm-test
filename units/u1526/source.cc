// u1526 – ceres::Problem::AddParameterBlock
// Trích từ internal/ceres/problem.cc, dòng 72–74 (chỉ để xem, không compile)

void Problem::AddParameterBlock(double* values, int size, Manifold* manifold) {
  impl_->AddParameterBlock(values, size, manifold);
}
