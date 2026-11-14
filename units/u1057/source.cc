// u1057 – ceres::ConditionedCostFunction::Evaluate
// Trích từ internal/ceres/conditioned_cost_function.cc, dòng 78–129 (chỉ để xem, không compile)

bool ConditionedCostFunction::Evaluate(double const* const* parameters,
                                       double* residuals,
                                       double** jacobians) const {
  bool success =
      wrapped_cost_function_->Evaluate(parameters, residuals, jacobians);
  if (!success) {
    return false;
  }

  for (int r = 0; r < wrapped_cost_function_->num_residuals(); r++) {
    // On output, we want to have
    // residuals[r] = conditioners[r](wrapped_residuals[r])
    // For parameter block i, column c,
    // jacobians[i][r*parameter_block_size_[i] + c] =
    //   = d residual[r] / d parameters[i][c]
    //   = conditioners[r]'(wrapped_residuals[r]) *
    //       d wrapped_residuals[r] / d parameters[i][c]
    if (conditioners_[r]) {
      double conditioner_derivative;
      double* conditioner_derivative_pointer = &conditioner_derivative;
      double** conditioner_derivative_pointer2 =
          &conditioner_derivative_pointer;
      if (!jacobians) {
        conditioner_derivative_pointer2 = nullptr;
      }

      double unconditioned_residual = residuals[r];
      double* parameter_pointer = &unconditioned_residual;
      success = conditioners_[r]->Evaluate(
          &parameter_pointer, &residuals[r], conditioner_derivative_pointer2);
      if (!success) {
        return false;
      }

      if (jacobians) {
        for (int i = 0;
             i < wrapped_cost_function_->parameter_block_sizes().size();
             i++) {
          if (jacobians[i]) {
            int parameter_block_size =
                wrapped_cost_function_->parameter_block_sizes()[i];
            VectorRef jacobian_row(jacobians[i] + r * parameter_block_size,
                                   parameter_block_size,
                                   1);
            jacobian_row *= conditioner_derivative;
          }
        }
      }
    }
  }
  return true;
}
