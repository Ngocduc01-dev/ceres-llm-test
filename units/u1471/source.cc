// u1471 – ceres::internal::ResidualBlock::Evaluate
// Trích từ internal/ceres/residual_block.cc, dòng 68–196 (chỉ để xem, không compile)

bool ResidualBlock::Evaluate(const bool apply_loss_function,
                             double* cost,
                             double* residuals,
                             double** jacobians,
                             double* scratch) const {
  const int num_parameter_blocks = NumParameterBlocks();
  const int num_residuals = cost_function_->num_residuals();

  // Collect the parameters from their blocks. This will rarely allocate, since
  // residuals taking more than 8 parameter block arguments are rare.
  FixedArray<const double*, 8> parameters(num_parameter_blocks);
  for (int i = 0; i < num_parameter_blocks; ++i) {
    parameters[i] = parameter_blocks_[i]->state();
  }

  // Put pointers into the scratch space into global_jacobians as appropriate.
  FixedArray<double*, 8> global_jacobians(num_parameter_blocks);
  if (jacobians != nullptr) {
    for (int i = 0; i < num_parameter_blocks; ++i) {
      const ParameterBlock* parameter_block = parameter_blocks_[i];
      if (jacobians[i] != nullptr &&
          parameter_block->PlusJacobian() != nullptr) {
        global_jacobians[i] = scratch;
        scratch += num_residuals * parameter_block->Size();
      } else {
        global_jacobians[i] = jacobians[i];
      }
    }
  }

  // If the caller didn't request residuals, use the scratch space for them.
  bool outputting_residuals = (residuals != nullptr);
  if (!outputting_residuals) {
    residuals = scratch;
  }

  // Invalidate the evaluation buffers so that we can check them after
  // the CostFunction::Evaluate call, to see if all the return values
  // that were required were written to and that they are finite.
  double** eval_jacobians =
      (jacobians != nullptr) ? global_jacobians.data() : nullptr;

  InvalidateEvaluation(*this, cost, residuals, eval_jacobians);

  if (!cost_function_->Evaluate(parameters.data(), residuals, eval_jacobians)) {
    return false;
  }

  if (!IsEvaluationValid(*this, parameters.data(), residuals, eval_jacobians)) {
    // clang-format off
    std::string message =
        "\n\n"
        "Error in evaluating the ResidualBlock.\n\n"
        "There are two possible reasons. Either the CostFunction did not evaluate and fill all    \n"  // NOLINT
        "residual and jacobians that were requested or there was a non-finite value (nan/infinite)\n"  // NOLINT
        "generated during the or jacobian computation. \n\n" +
        EvaluationToString(
            *this, parameters.data(), cost, residuals, eval_jacobians);
    // clang-format on
    LOG(WARNING) << message;
    return false;
  }

  double squared_norm = VectorRef(residuals, num_residuals).squaredNorm();

  // Update the plus_jacobian for the manifolds.
  if (jacobians != nullptr) {
    for (int i = 0; i < num_parameter_blocks; ++i) {
      if (jacobians[i] != nullptr) {
        const ParameterBlock* parameter_block = parameter_blocks_[i];

        // Apply the Manifold::PlusJacobian to the ambient jacobians.
        if (parameter_block->PlusJacobian() != nullptr) {
          // jacobians[i] = global_jacobians[i] * global_to_local_jacobian.
          MatrixMatrixMultiply<Dynamic, Dynamic, Dynamic, Dynamic, 0>(
              global_jacobians[i],
              num_residuals,
              parameter_block->Size(),
              parameter_block->PlusJacobian(),
              parameter_block->Size(),
              parameter_block->TangentSize(),
              jacobians[i],
              0,
              0,
              num_residuals,
              parameter_block->TangentSize());
        }
      }
    }
  }

  if (loss_function_ == nullptr || !apply_loss_function) {
    *cost = 0.5 * squared_norm;
    return true;
  }

  double rho[3];
  loss_function_->Evaluate(squared_norm, rho);
  *cost = 0.5 * rho[0];

  // No jacobians and not outputting residuals? All done. Doing an early exit
  // here avoids constructing the "Corrector" object below in a common case.
  if (jacobians == nullptr && !outputting_residuals) {
    return true;
  }

  // Correct for the effects of the loss function. The jacobians need to be
  // corrected before the residuals, since they use the uncorrected residuals.
  Corrector correct(squared_norm, rho);
  if (jacobians != nullptr) {
    for (int i = 0; i < num_parameter_blocks; ++i) {
      if (jacobians[i] != nullptr) {
        const ParameterBlock* parameter_block = parameter_blocks_[i];

        // Correct the jacobians for the loss function.
        correct.CorrectJacobian(num_residuals,
                                parameter_block->TangentSize(),
                                residuals,
                                jacobians[i]);
      }
    }
  }

  // Correct the residuals with the loss function.
  if (outputting_residuals) {
    correct.CorrectResiduals(num_residuals, residuals);
  }
  return true;
}
