// u1306 – ceres::GradientChecker::Probe
// Trích từ internal/ceres/gradient_checker.cc, dòng 141–283 (chỉ để xem, không compile)

bool GradientChecker::Probe(double const* const* parameters,
                            double relative_precision,
                            ProbeResults* results_param) const {
  int num_residuals = function_->num_residuals();

  // Make sure that we have a place to store results, no matter if the user has
  // provided an output argument.
  ProbeResults* results;
  ProbeResults results_local;
  if (results_param != nullptr) {
    results = results_param;
    results->residuals.resize(0);
    results->jacobians.clear();
    results->numeric_jacobians.clear();
    results->local_jacobians.clear();
    results->local_numeric_jacobians.clear();
    results->error_log.clear();
  } else {
    results = &results_local;
  }
  results->maximum_relative_error = 0.0;
  results->return_value = true;

  // Evaluate the derivative using the user supplied code.
  std::vector<Matrix>& jacobians = results->jacobians;
  std::vector<Matrix>& local_jacobians = results->local_jacobians;
  if (!EvaluateCostFunction(function_,
                            parameters,
                            manifolds_,
                            &results->residuals,
                            &jacobians,
                            &local_jacobians)) {
    results->error_log = "Function evaluation with Jacobians failed.";
    results->return_value = false;
  }

  // Evaluate the derivative using numeric derivatives.
  std::vector<Matrix>& numeric_jacobians = results->numeric_jacobians;
  std::vector<Matrix>& local_numeric_jacobians =
      results->local_numeric_jacobians;
  Vector finite_diff_residuals;
  if (!EvaluateCostFunction(finite_diff_cost_function_.get(),
                            parameters,
                            manifolds_,
                            &finite_diff_residuals,
                            &numeric_jacobians,
                            &local_numeric_jacobians)) {
    results->error_log +=
        "\nFunction evaluation with numerical "
        "differentiation failed.";
    results->return_value = false;
  }

  if (!results->return_value) {
    return false;
  }

  for (int i = 0; i < num_residuals; ++i) {
    if (!IsClose(results->residuals[i],
                 finite_diff_residuals[i],
                 relative_precision,
                 nullptr,
                 nullptr)) {
      results->error_log =
          "Function evaluation with and without Jacobians "
          "resulted in different residuals.";
      LOG(INFO) << results->residuals.transpose();
      LOG(INFO) << finite_diff_residuals.transpose();
      return false;
    }
  }

  // See if any elements have relative error larger than the threshold.
  int num_bad_jacobian_components = 0;
  double& worst_relative_error = results->maximum_relative_error;
  worst_relative_error = 0;

  // Accumulate the error message for all the jacobians, since it won't get
  // output if there are no bad jacobian components.
  std::string error_log;
  for (int k = 0; k < function_->parameter_block_sizes().size(); k++) {
    StringAppendF(&error_log,
                  "========== "
                  "Jacobian for block %d: (%ld by %ld)) "
                  "==========\n",
                  k,
                  static_cast<long>(local_jacobians[k].rows()),
                  static_cast<long>(local_jacobians[k].cols()));
    // The funny spacing creates appropriately aligned column headers.
    error_log +=
        " block  row  col        user dx/dy    num diff dx/dy         "
        "abs error    relative error         parameter          residual\n";

    for (int i = 0; i < local_jacobians[k].rows(); i++) {
      for (int j = 0; j < local_jacobians[k].cols(); j++) {
        double term_jacobian = local_jacobians[k](i, j);
        double finite_jacobian = local_numeric_jacobians[k](i, j);
        double relative_error, absolute_error;
        bool bad_jacobian_entry = !IsClose(term_jacobian,
                                           finite_jacobian,
                                           relative_precision,
                                           &relative_error,
                                           &absolute_error);
        worst_relative_error = std::max(worst_relative_error, relative_error);

        StringAppendF(&error_log,
                      "%6d %4d %4d %17g %17g %17g %17g %17g %17g",
                      k,
                      i,
                      j,
                      term_jacobian,
                      finite_jacobian,
                      absolute_error,
                      relative_error,
                      parameters[k][j],
                      results->residuals[i]);

        if (bad_jacobian_entry) {
          num_bad_jacobian_components++;
          StringAppendF(&error_log,
                        " ------ (%d,%d,%d) Relative error worse than %g",
                        k,
                        i,
                        j,
                        relative_precision);
        }
        error_log += "\n";
      }
    }
  }

  // Since there were some bad errors, dump comprehensive debug info.
  if (num_bad_jacobian_components) {
    std::string header = StringPrintf(
        "\nDetected %d bad Jacobian component(s). "
        "Worst relative error was %g.\n",
        num_bad_jacobian_components,
        worst_relative_error);
    results->error_log = header + "\n" + error_log;
    return false;
  }
  return true;
}
