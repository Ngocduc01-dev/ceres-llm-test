// u1171 – ceres::internal::LineSearch::Create
// Trích từ internal/ceres/line_search.cc, dòng 71–86 (chỉ để xem, không compile)

std::unique_ptr<LineSearch> LineSearch::Create(
    const LineSearchType line_search_type,
    const LineSearch::Options& options,
    std::string* error) {
  switch (line_search_type) {
    case ceres::ARMIJO:
      return std::make_unique<ArmijoLineSearch>(options);
    case ceres::WOLFE:
      return std::make_unique<WolfeLineSearch>(options);
    default:
      *error = std::string("Invalid line search algorithm type: ") +
               LineSearchTypeToString(line_search_type) +
               std::string(", unable to create line search.");
  }
  return nullptr;
}
