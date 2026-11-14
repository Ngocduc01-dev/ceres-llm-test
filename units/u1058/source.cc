// u1058 – ceres::DynamicNumericDiffCostFunction::Evaluate
// Trích từ include/ceres/dynamic_numeric_diff_cost_function.h, dòng 97–154 (chỉ để xem, không compile)

  bool Evaluate(double const* const* parameters,
                double* residuals,
                double** jacobians) const override {
    using internal::NumericDiff;
    CHECK_GT(num_residuals(), 0)
        << "You must call DynamicNumericDiffCostFunction::SetNumResiduals() "
        << "before DynamicNumericDiffCostFunction::Evaluate().";

    const std::vector<int32_t>& block_sizes = parameter_block_sizes();
    CHECK(!block_sizes.empty())
        << "You must call DynamicNumericDiffCostFunction::AddParameterBlock() "
        << "before DynamicNumericDiffCostFunction::Evaluate().";

    const bool status =
        internal::VariadicEvaluate<internal::DynamicParameterDims>(
            *functor_.get(), parameters, residuals);
    if (jacobians == nullptr || !status) {
      return status;
    }

    // Create local space for a copy of the parameters which will get mutated.
    int parameters_size = accumulate(block_sizes.begin(), block_sizes.end(), 0);
    std::vector<double> parameters_copy(parameters_size);
    std::vector<double*> parameters_references_copy(block_sizes.size());
    parameters_references_copy[0] = &parameters_copy[0];
    for (size_t block = 1; block < block_sizes.size(); ++block) {
      parameters_references_copy[block] =
          parameters_references_copy[block - 1] + block_sizes[block - 1];
    }

    // Copy the parameters into the local temp space.
    for (size_t block = 0; block < block_sizes.size(); ++block) {
      memcpy(parameters_references_copy[block],
             parameters[block],
             block_sizes[block] * sizeof(*parameters[block]));
    }

    for (size_t block = 0; block < block_sizes.size(); ++block) {
      if (jacobians[block] != nullptr &&
          !NumericDiff<CostFunctor,
                       kMethod,
                       ceres::DYNAMIC,
                       internal::DynamicParameterDims,
                       ceres::DYNAMIC,
                       ceres::DYNAMIC>::
              EvaluateJacobianForParameterBlock(functor_.get(),
                                                residuals,
                                                options_,
                                                this->num_residuals(),
                                                block,
                                                block_sizes[block],
                                                &parameters_references_copy[0],
                                                jacobians[block])) {
        return false;
      }
    }
    return true;
  }
