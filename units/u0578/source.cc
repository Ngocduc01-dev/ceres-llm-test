// u0578 – ceres::internal::DoglegStrategy::ComputeSubspaceStepFromRoot
// Trích từ internal/ceres/dogleg_strategy.cc, dòng 447–451 (chỉ để xem, không compile)

DoglegStrategy::Vector2d DoglegStrategy::ComputeSubspaceStepFromRoot(
    double y) const {
  const Matrix2d B_i = subspace_B_ + y * Matrix2d::Identity();
  return -B_i.partialPivLu().solve(subspace_g_);
}
