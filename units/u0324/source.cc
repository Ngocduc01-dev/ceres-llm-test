// u0324 – ceres::internal::LineSearchFunction::DirectionInfinityNorm
// Trích từ internal/ceres/line_search.cc, dòng 145–147 (chỉ để xem, không compile)

double LineSearchFunction::DirectionInfinityNorm() const {
  return direction_.lpNorm<Eigen::Infinity>();
}
