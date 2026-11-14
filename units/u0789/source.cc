// u0789 – ceres::internal::DoglegStrategy::EvaluateSubspaceModel
// Trích từ internal/ceres/dogleg_strategy.cc, dòng 455–457 (chỉ để xem, không compile)

double DoglegStrategy::EvaluateSubspaceModel(const Vector2d& x) const {
  return 0.5 * x.dot(subspace_B_ * x) + subspace_g_.dot(x);
}
