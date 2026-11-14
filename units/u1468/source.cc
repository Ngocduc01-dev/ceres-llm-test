// u1468 – ceres::internal::CoordinateDescentMinimizer::CreateOrdering
// Trích từ internal/ceres/coordinate_descent_minimizer.cc, dòng 265–271 (chỉ để xem, không compile)

std::shared_ptr<ParameterBlockOrdering>
CoordinateDescentMinimizer::CreateOrdering(const Program& program) {
  auto ordering = std::make_shared<ParameterBlockOrdering>();
  ComputeRecursiveIndependentSetOrdering(program, ordering.get());
  ordering->Reverse();
  return ordering;
}
