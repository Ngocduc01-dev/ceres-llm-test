// u1274 – ceres::(anonymous)::StringifyOrdering
// Trích từ internal/ceres/solver.cc, dòng 496–506 (chỉ để xem, không compile)

void StringifyOrdering(const std::vector<int>& ordering, std::string* report) {
  if (ordering.empty()) {
    internal::StringAppendF(report, "AUTOMATIC");
    return;
  }

  for (int i = 0; i < ordering.size() - 1; ++i) {
    internal::StringAppendF(report, "%d,", ordering[i]);
  }
  internal::StringAppendF(report, "%d", ordering.back());
}
