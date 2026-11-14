// u0969 – ceres::internal::(anonymous)::EvaluateGradientNorms
// Trích từ internal/ceres/line_search_minimizer.cc, dòng 65–81 (chỉ để xem, không compile)

bool EvaluateGradientNorms(Evaluator* evaluator,
                           const Vector& x,
                           LineSearchMinimizer::State* state,
                           std::string* message) {
  Vector negative_gradient = -state->gradient;
  Vector projected_gradient_step(x.size());
  if (!evaluator->Plus(
          x.data(), negative_gradient.data(), projected_gradient_step.data())) {
    *message = "projected_gradient_step = Plus(x, -gradient) failed.";
    return false;
  }

  state->gradient_squared_norm = (x - projected_gradient_step).squaredNorm();
  state->gradient_max_norm =
      (x - projected_gradient_step).lpNorm<Eigen::Infinity>();
  return true;
}
