// u1248 – ceres::internal::ProblemImpl::HasManifold
// Trích từ internal/ceres/problem_impl.cc, dòng 530–532 (chỉ để xem, không compile)

bool ProblemImpl::HasManifold(const double* values) const {
  return GetManifold(values) != nullptr;
}
