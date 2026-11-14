// u1409 – ceres::internal::Program::IsFeasible
// Trích từ internal/ceres/program.cc, dòng 229–285 (chỉ để xem, không compile)

bool Program::IsFeasible(std::string* message) const {
  CHECK(message != nullptr);
  for (auto* parameter_block : parameter_blocks_) {
    const double* parameters = parameter_block->user_state();
    const int size = parameter_block->Size();
    if (parameter_block->IsConstant()) {
      // Constant parameter blocks must start in the feasible region
      // to ultimately produce a feasible solution, since Ceres cannot
      // change them.
      for (int j = 0; j < size; ++j) {
        const double lower_bound = parameter_block->LowerBoundForParameter(j);
        const double upper_bound = parameter_block->UpperBoundForParameter(j);
        if (parameters[j] < lower_bound || parameters[j] > upper_bound) {
          *message = StringPrintf(
              "ParameterBlock: %p with size %d has at least one infeasible "
              "value."
              "\nFirst infeasible value is at index: %d."
              "\nLower bound: %e, value: %e, upper bound: %e"
              "\nParameter block values: ",
              parameters,
              size,
              j,
              lower_bound,
              parameters[j],
              upper_bound);
          AppendArrayToString(size, parameters, message);
          return false;
        }
      }
    } else {
      // Variable parameter blocks must have non-empty feasible
      // regions, otherwise there is no way to produce a feasible
      // solution.
      for (int j = 0; j < size; ++j) {
        const double lower_bound = parameter_block->LowerBoundForParameter(j);
        const double upper_bound = parameter_block->UpperBoundForParameter(j);
        if (lower_bound >= upper_bound) {
          *message = StringPrintf(
              "ParameterBlock: %p with size %d has at least one infeasible "
              "bound."
              "\nFirst infeasible bound is at index: %d."
              "\nLower bound: %e, upper bound: %e"
              "\nParameter block values: ",
              parameters,
              size,
              j,
              lower_bound,
              upper_bound);
          AppendArrayToString(size, parameters, message);
          return false;
        }
      }
    }
  }

  return true;
}
