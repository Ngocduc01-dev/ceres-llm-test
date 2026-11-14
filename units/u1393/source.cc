// u1393 – ceres::internal::(anonymous)::GradientCheckingCostFunction::Evaluate
// Trích từ internal/ceres/gradient_checking_cost_function.cc, dòng 79–119 (chỉ để xem, không compile)

  bool Evaluate(double const* const* parameters,
                double* residuals,
                double** jacobians) const final {
    if (!jacobians) {
      // Nothing to check in this case; just forward.
      return function_->Evaluate(parameters, residuals, nullptr);
    }

    GradientChecker::ProbeResults results;
    bool okay =
        gradient_checker_.Probe(parameters, relative_precision_, &results);

    // If the cost function returned false, there's nothing we can say about
    // the gradients.
    if (results.return_value == false) {
      return false;
    }

    // Copy the residuals.
    const int num_residuals = function_->num_residuals();
    MatrixRef(residuals, num_residuals, 1) = results.residuals;

    // Copy the original jacobian blocks into the jacobians array.
    const std::vector<int32_t>& block_sizes =
        function_->parameter_block_sizes();
    for (int k = 0; k < block_sizes.size(); k++) {
      if (jacobians[k] != nullptr) {
        MatrixRef(jacobians[k],
                  results.jacobians[k].rows(),
                  results.jacobians[k].cols()) = results.jacobians[k];
      }
    }

    if (!okay) {
      std::string error_log =
          "Gradient Error detected!\nExtra info for this residual: " +
          extra_info_ + "\n" + results.error_log;
      callback_->SetGradientErrorDetected(error_log);
    }
    return true;
  }
