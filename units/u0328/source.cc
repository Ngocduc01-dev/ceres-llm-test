// u0328 – ceres::internal::LineSearchMinimizer::State::State
// Trích từ internal/ceres/line_search_minimizer.h, dòng 49–55 (chỉ để xem, không compile)

    State(int /*num_parameters*/, int num_effective_parameters)
        : cost(0.0),
          gradient(num_effective_parameters),
          gradient_squared_norm(0.0),
          search_direction(num_effective_parameters),
          directional_derivative(0.0),
          step_size(0.0) {}
