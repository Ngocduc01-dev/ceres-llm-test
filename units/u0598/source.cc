// u0598 – ceres::internal::(anonymous)::RegionsAlias
// Trích từ internal/ceres/problem_impl.cc, dòng 70–72 (chỉ để xem, không compile)

bool RegionsAlias(const double* a, int size_a, const double* b, int size_b) {
  return (a < b) ? b < (a + size_a) : a < (b + size_b);
}
