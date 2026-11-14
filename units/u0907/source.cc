// u0907 – ceres::internal::CoordinateDescentMinimizer::CoordinateDescentMinimizer
// Trích từ internal/ceres/coordinate_descent_minimizer.cc, dòng 57–60 (chỉ để xem, không compile)

CoordinateDescentMinimizer::CoordinateDescentMinimizer(ContextImpl* context)
    : context_(context) {
  CHECK(context_ != nullptr);
}
