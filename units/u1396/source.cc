// u1396 – ceres::internal::operator<<
// Trích từ internal/ceres/line_search.cc, dòng 61–64 (chỉ để xem, không compile)

std::ostream& operator<<(std::ostream& os, const FunctionSample& sample) {
  os << sample.ToDebugString();
  return os;
}
