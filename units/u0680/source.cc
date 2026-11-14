// u0680 – ceres::internal::LineSearchFunction::Init
// Trích từ internal/ceres/line_search.cc, dòng 96–99 (chỉ để xem, không compile)

void LineSearchFunction::Init(const Vector& position, const Vector& direction) {
  position_ = position;
  direction_ = direction;
}
