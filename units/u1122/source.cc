// u1122 – ceres::internal::LineSearchFunction::Evaluate
// Trích từ internal/ceres/line_search.cc, dòng 101–143 (chỉ để xem, không compile)

void LineSearchFunction::Evaluate(const double x,
                                  const bool evaluate_gradient,
                                  FunctionSample* output) {
  output->x = x;
  output->vector_x_is_valid = false;
  output->value_is_valid = false;
  output->gradient_is_valid = false;
  output->vector_gradient_is_valid = false;

  scaled_direction_ = output->x * direction_;
  output->vector_x.resize(position_.rows(), 1);
  if (!evaluator_->Plus(position_.data(),
                        scaled_direction_.data(),
                        output->vector_x.data())) {
    return;
  }
  output->vector_x_is_valid = true;

  double* gradient = nullptr;
  if (evaluate_gradient) {
    output->vector_gradient.resize(direction_.rows(), 1);
    gradient = output->vector_gradient.data();
  }
  const bool eval_status = evaluator_->Evaluate(
      output->vector_x.data(), &(output->value), nullptr, gradient, nullptr);

  if (!eval_status || !std::isfinite(output->value)) {
    return;
  }

  output->value_is_valid = true;
  if (!evaluate_gradient) {
    return;
  }

  output->gradient = direction_.dot(output->vector_gradient);
  if (!std::isfinite(output->gradient)) {
    return;
  }

  output->gradient_is_valid = true;
  output->vector_gradient_is_valid = true;
}
