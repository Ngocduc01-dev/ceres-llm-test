// u0681 – ceres::internal::SteepestDescent::NextDirection
// Trích từ internal/ceres/line_search_direction.cc, dòng 45–50 (chỉ để xem, không compile)

  bool NextDirection(const LineSearchMinimizer::State& /*previous*/,
                     const LineSearchMinimizer::State& current,
                     Vector* search_direction) override {
    *search_direction = -current.gradient;
    return true;
  }
