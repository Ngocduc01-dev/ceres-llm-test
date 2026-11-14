// u1408 – ceres::internal::EvaluationToString
// Trích từ internal/ceres/residual_block_utils.cc, dòng 65–116 (chỉ để xem, không compile)

std::string EvaluationToString(const ResidualBlock& block,
                               double const* const* parameters,
                               double* cost,
                               double* residuals,
                               double** jacobians) {
  CHECK(cost != nullptr);
  CHECK(residuals != nullptr);

  const int num_parameter_blocks = block.NumParameterBlocks();
  const int num_residuals = block.NumResiduals();
  std::string result = "";

  // clang-format off
  StringAppendF(&result,
                "Residual Block size: %d parameter blocks x %d residuals\n\n",
                num_parameter_blocks, num_residuals);
  result +=
      "For each parameter block, the value of the parameters are printed in the first column   \n"  // NOLINT
      "and the value of the jacobian under the corresponding residual. If a ParameterBlock was \n"  // NOLINT
      "held constant then the corresponding jacobian is printed as 'Not Computed'. If an entry \n"  // NOLINT
      "of the Jacobian/residual array was requested but was not written to by user code, it is \n"  // NOLINT
      "indicated by 'Uninitialized'. This is an error. Residuals or Jacobian values evaluating \n"  // NOLINT
      "to Inf or NaN is also an error.  \n\n"; // NOLINT
  // clang-format on

  std::string space = "Residuals:     ";
  result += space;
  AppendArrayToString(num_residuals, residuals, &result);
  StringAppendF(&result, "\n\n");

  for (int i = 0; i < num_parameter_blocks; ++i) {
    const int parameter_block_size = block.parameter_blocks()[i]->Size();
    StringAppendF(
        &result, "Parameter Block %d, size: %d\n", i, parameter_block_size);
    StringAppendF(&result, "\n");
    for (int j = 0; j < parameter_block_size; ++j) {
      AppendArrayToString(1, parameters[i] + j, &result);
      StringAppendF(&result, "| ");
      for (int k = 0; k < num_residuals; ++k) {
        AppendArrayToString(1,
                            (jacobians != nullptr && jacobians[i] != nullptr)
                                ? jacobians[i] + k * parameter_block_size + j
                                : nullptr,
                            &result);
      }
      StringAppendF(&result, "\n");
    }
    StringAppendF(&result, "\n");
  }
  StringAppendF(&result, "\n");
  return result;
}
