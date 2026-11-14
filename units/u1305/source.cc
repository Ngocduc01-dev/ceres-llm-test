// u1305 – ceres::internal::NumericDiff::EvaluateJacobianForParameterBlock
// Trích từ include/ceres/internal/numeric_diff.h, dòng 63–170 (chỉ để xem, không compile)

  static bool EvaluateJacobianForParameterBlock(
      const CostFunctor* functor,
      const double* residuals_at_eval_point,
      const NumericDiffOptions& options,
      int num_residuals,
      int parameter_block_index,
      int parameter_block_size,
      double** parameters,
      double* jacobian) {
    using Eigen::ColMajor;
    using Eigen::Map;
    using Eigen::Matrix;
    using Eigen::RowMajor;

    DCHECK(jacobian);

    const int num_residuals_internal =
        (kNumResiduals != ceres::DYNAMIC ? kNumResiduals : num_residuals);
    const int parameter_block_index_internal =
        (kParameterBlock != ceres::DYNAMIC ? kParameterBlock
                                           : parameter_block_index);
    const int parameter_block_size_internal =
        (kParameterBlockSize != ceres::DYNAMIC ? kParameterBlockSize
                                               : parameter_block_size);

    using ResidualVector = Matrix<double, kNumResiduals, 1>;
    using ParameterVector = Matrix<double, kParameterBlockSize, 1>;

    // The convoluted reasoning for choosing the Row/Column major
    // ordering of the matrix is an artifact of the restrictions in
    // Eigen that prevent it from creating RowMajor matrices with a
    // single column. In these cases, we ask for a ColMajor matrix.
    using JacobianMatrix =
        Matrix<double,
               kNumResiduals,
               kParameterBlockSize,
               (kParameterBlockSize == 1) ? ColMajor : RowMajor>;

    Map<JacobianMatrix> parameter_jacobian(
        jacobian, num_residuals_internal, parameter_block_size_internal);

    Map<ParameterVector> x_plus_delta(
        parameters[parameter_block_index_internal],
        parameter_block_size_internal);
    ParameterVector x(x_plus_delta);
    ParameterVector step_size =
        x.array().abs() * ((kMethod == RIDDERS)
                               ? options.ridders_relative_initial_step_size
                               : options.relative_step_size);

    // It is not a good idea to make the step size arbitrarily
    // small. This will lead to problems with round off and numerical
    // instability when dividing by the step size. The general
    // recommendation is to not go down below sqrt(epsilon).
    double min_step_size = std::sqrt(std::numeric_limits<double>::epsilon());

    // For Ridders' method, the initial step size is required to be large,
    // thus ridders_relative_initial_step_size is used.
    if (kMethod == RIDDERS) {
      min_step_size =
          (std::max)(min_step_size, options.ridders_relative_initial_step_size);
    }

    // For each parameter in the parameter block, use finite differences to
    // compute the derivative for that parameter.
    FixedArray<double> temp_residual_array(num_residuals_internal);
    FixedArray<double> residual_array(num_residuals_internal);
    Map<ResidualVector> residuals(residual_array.data(),
                                  num_residuals_internal);

    for (int j = 0; j < parameter_block_size_internal; ++j) {
      const double delta = (std::max)(min_step_size, step_size(j));

      if (kMethod == RIDDERS) {
        if (!EvaluateRiddersJacobianColumn(functor,
                                           j,
                                           delta,
                                           options,
                                           num_residuals_internal,
                                           parameter_block_size_internal,
                                           x.data(),
                                           residuals_at_eval_point,
                                           parameters,
                                           x_plus_delta.data(),
                                           temp_residual_array.data(),
                                           residual_array.data())) {
          return false;
        }
      } else {
        if (!EvaluateJacobianColumn(functor,
                                    j,
                                    delta,
                                    num_residuals_internal,
                                    parameter_block_size_internal,
                                    x.data(),
                                    residuals_at_eval_point,
                                    parameters,
                                    x_plus_delta.data(),
                                    temp_residual_array.data(),
                                    residual_array.data())) {
          return false;
        }
      }

      parameter_jacobian.col(j).matrix() = residuals;
    }
    return true;
  }
