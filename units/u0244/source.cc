// u0244 – CallbackCostFunction::Evaluate
// Trích từ internal/ceres/c_api.cc, dòng 82–87 (chỉ để xem, không compile)

  bool Evaluate(double const* const* parameters,
                double* residuals,
                double** jacobians) const final {
    return (*cost_function_)(
        user_data_, const_cast<double**>(parameters), residuals, jacobians);
  }
