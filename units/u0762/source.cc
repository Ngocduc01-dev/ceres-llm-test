// u0762 – ceres::internal::NonlinearConjugateGradient::NextDirection
// Trích từ internal/ceres/line_search_direction.cc, dòng 60–93 (chỉ để xem, không compile)

  bool NextDirection(const LineSearchMinimizer::State& previous,
                     const LineSearchMinimizer::State& current,
                     Vector* search_direction) override {
    double beta = 0.0;
    Vector gradient_change;
    switch (type_) {
      case FLETCHER_REEVES:
        beta = current.gradient_squared_norm / previous.gradient_squared_norm;
        break;
      case POLAK_RIBIERE:
        gradient_change = current.gradient - previous.gradient;
        beta = (current.gradient.dot(gradient_change) /
                previous.gradient_squared_norm);
        break;
      case HESTENES_STIEFEL:
        gradient_change = current.gradient - previous.gradient;
        beta = (current.gradient.dot(gradient_change) /
                previous.search_direction.dot(gradient_change));
        break;
      default:
        LOG(FATAL) << "Unknown nonlinear conjugate gradient type: " << type_;
    }

    *search_direction = -current.gradient + beta * previous.search_direction;
    const double directional_derivative =
        current.gradient.dot(*search_direction);
    if (directional_derivative > -function_tolerance_) {
      LOG(WARNING) << "Restarting non-linear conjugate gradients: "
                   << directional_derivative;
      *search_direction = -current.gradient;
    }

    return true;
  }
