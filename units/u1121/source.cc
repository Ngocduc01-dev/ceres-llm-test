// u1121 – ceres::DynamicCostFunctionToFunctor::operator()
// Trích từ include/ceres/dynamic_cost_function_to_functor.h, dòng 117–184 (chỉ để xem, không compile)

  template <typename JetT>
  bool operator()(JetT const* const* inputs, JetT* output) const {
    const std::vector<int32_t>& parameter_block_sizes =
        cost_function_->parameter_block_sizes();
    const int num_parameter_blocks =
        static_cast<int>(parameter_block_sizes.size());
    const int num_residuals = cost_function_->num_residuals();
    const int num_parameters = std::accumulate(
        parameter_block_sizes.begin(), parameter_block_sizes.end(), 0);

    internal::FixedArray<double> parameters(num_parameters);
    internal::FixedArray<double*> parameter_blocks(num_parameter_blocks);
    internal::FixedArray<double> jacobians(num_residuals * num_parameters);
    internal::FixedArray<double*> jacobian_blocks(num_parameter_blocks);
    internal::FixedArray<double> residuals(num_residuals);

    // Build a set of arrays to get the residuals and jacobians from
    // the CostFunction wrapped by this functor.
    double* parameter_ptr = parameters.data();
    double* jacobian_ptr = jacobians.data();
    for (int i = 0; i < num_parameter_blocks; ++i) {
      parameter_blocks[i] = parameter_ptr;
      jacobian_blocks[i] = jacobian_ptr;
      for (int j = 0; j < parameter_block_sizes[i]; ++j) {
        *parameter_ptr++ = inputs[i][j].a;
      }
      jacobian_ptr += num_residuals * parameter_block_sizes[i];
    }

    if (!cost_function_->Evaluate(parameter_blocks.data(),
                                  residuals.data(),
                                  jacobian_blocks.data())) {
      return false;
    }

    // Now that we have the incoming Jets, which are carrying the
    // partial derivatives of each of the inputs w.r.t to some other
    // underlying parameters. The derivative of the outputs of the
    // cost function w.r.t to the same underlying parameters can now
    // be computed by applying the chain rule.
    //
    //  d output[i]               d output[i]   d input[j]
    //  --------------  = sum_j   ----------- * ------------
    //  d parameter[k]            d input[j]    d parameter[k]
    //
    // d input[j]
    // --------------  = inputs[j], so
    // d parameter[k]
    //
    //  outputJet[i]  = sum_k jacobian[i][k] * inputJet[k]
    //
    // The following loop, iterates over the residuals, computing one
    // output jet at a time.
    for (int i = 0; i < num_residuals; ++i) {
      output[i].a = residuals[i];
      output[i].v.setZero();

      for (int j = 0; j < num_parameter_blocks; ++j) {
        const int32_t block_size = parameter_block_sizes[j];
        for (int k = 0; k < parameter_block_sizes[j]; ++k) {
          output[i].v +=
              jacobian_blocks[j][i * block_size + k] * inputs[j][k].v;
        }
      }
    }

    return true;
  }
