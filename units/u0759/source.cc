// u0759 – ceres::internal::NumericDiff::EvaluateJacobianColumn
// Trích từ include/ceres/internal/numeric_diff.h, dòng 172–232 (chỉ để xem, không compile)

  static bool EvaluateJacobianColumn(const CostFunctor* functor,
                                     int parameter_index,
                                     double delta,
                                     int num_residuals,
                                     int parameter_block_size,
                                     const double* x_ptr,
                                     const double* residuals_at_eval_point,
                                     double** parameters,
                                     double* x_plus_delta_ptr,
                                     double* temp_residuals_ptr,
                                     double* residuals_ptr) {
    using Eigen::Map;
    using Eigen::Matrix;

    using ResidualVector = Matrix<double, kNumResiduals, 1>;
    using ParameterVector = Matrix<double, kParameterBlockSize, 1>;

    Map<const ParameterVector> x(x_ptr, parameter_block_size);
    Map<ParameterVector> x_plus_delta(x_plus_delta_ptr, parameter_block_size);

    Map<ResidualVector> residuals(residuals_ptr, num_residuals);
    Map<ResidualVector> temp_residuals(temp_residuals_ptr, num_residuals);

    // Mutate 1 element at a time and then restore.
    x_plus_delta(parameter_index) = x(parameter_index) + delta;

    if (!VariadicEvaluate<ParameterDims>(
            *functor, parameters, residuals.data())) {
      return false;
    }

    // Compute this column of the jacobian in 3 steps:
    // 1. Store residuals for the forward part.
    // 2. Subtract residuals for the backward (or 0) part.
    // 3. Divide out the run.
    double one_over_delta = 1.0 / delta;
    if (kMethod == CENTRAL || kMethod == RIDDERS) {
      // Compute the function on the other side of x(parameter_index).
      x_plus_delta(parameter_index) = x(parameter_index) - delta;

      if (!VariadicEvaluate<ParameterDims>(
              *functor, parameters, temp_residuals.data())) {
        return false;
      }

      residuals -= temp_residuals;
      one_over_delta /= 2;
    } else {
      // Forward difference only; reuse existing residuals evaluation.
      residuals -=
          Map<const ResidualVector>(residuals_at_eval_point, num_residuals);
    }

    // Restore x_plus_delta.
    x_plus_delta(parameter_index) = x(parameter_index);

    // Divide out the run to get slope.
    residuals *= one_over_delta;

    return true;
  }
