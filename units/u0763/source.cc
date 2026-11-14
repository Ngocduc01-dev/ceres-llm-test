// u0763 – ceres::internal::LineSearchDirection::Create
// Trích từ internal/ceres/line_search_direction.cc, dòng 341–367 (chỉ để xem, không compile)

std::unique_ptr<LineSearchDirection> LineSearchDirection::Create(
    const LineSearchDirection::Options& options) {
  if (options.type == STEEPEST_DESCENT) {
    return std::make_unique<SteepestDescent>();
  }

  if (options.type == NONLINEAR_CONJUGATE_GRADIENT) {
    return std::make_unique<NonlinearConjugateGradient>(
        options.nonlinear_conjugate_gradient_type, options.function_tolerance);
  }

  if (options.type == ceres::LBFGS) {
    return std::make_unique<ceres::internal::LBFGS>(
        options.num_parameters,
        options.max_lbfgs_rank,
        options.use_approximate_eigenvalue_bfgs_scaling);
  }

  if (options.type == ceres::BFGS) {
    return std::make_unique<ceres::internal::BFGS>(
        options.num_parameters,
        options.use_approximate_eigenvalue_bfgs_scaling);
  }

  LOG(ERROR) << "Unknown line search direction type: " << options.type;
  return nullptr;
}
