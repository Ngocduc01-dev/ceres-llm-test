// u0412 – ceres::Solver::Summary::IsSolutionUsable
// Trích từ internal/ceres/solver.cc, dòng 1136–1138 (chỉ để xem, không compile)

bool Solver::Summary::IsSolutionUsable() const {
  return internal::IsSolutionUsable(*this);
}
