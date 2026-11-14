// u1481 – ceres::internal::Program::RemoveFixedBlocks
// Trích từ internal/ceres/program.cc, dòng 305–411 (chỉ để xem, không compile)

bool Program::RemoveFixedBlocks(std::vector<double*>* removed_parameter_blocks,
                                double* fixed_cost,
                                std::string* error) {
  CHECK(removed_parameter_blocks != nullptr);
  CHECK(fixed_cost != nullptr);
  CHECK(error != nullptr);

  std::unique_ptr<double[]> residual_block_evaluate_scratch;
  residual_block_evaluate_scratch =
      std::make_unique<double[]>(MaxScratchDoublesNeededForEvaluate());
  *fixed_cost = 0.0;

  bool need_to_call_prepare_for_evaluation = evaluation_callback_ != nullptr;

  // Mark all the parameters as unused. Abuse the index member of the
  // parameter blocks for the marking.
  for (auto* parameter_block : parameter_blocks_) {
    parameter_block->set_index(-1);
  }

  // Filter out residual that have all-constant parameters, and mark
  // all the parameter blocks that appear in residuals.
  int num_active_residual_blocks = 0;
  for (int i = 0; i < residual_blocks_.size(); ++i) {
    ResidualBlock* residual_block = residual_blocks_[i];
    int num_parameter_blocks = residual_block->NumParameterBlocks();

    // Determine if the residual block is fixed, and also mark varying
    // parameters that appear in the residual block.
    bool all_constant = true;
    for (int k = 0; k < num_parameter_blocks; k++) {
      ParameterBlock* parameter_block = residual_block->parameter_blocks()[k];
      if (!parameter_block->IsConstant()) {
        all_constant = false;
        parameter_block->set_index(1);
      }
    }

    if (!all_constant) {
      residual_blocks_[num_active_residual_blocks++] = residual_block;
      continue;
    }

    // This is an exceedingly rare case, where the user has residual
    // blocks which are effectively constant but they are also
    // performance sensitive enough to add an EvaluationCallback.
    //
    // In this case before we evaluate the cost of the constant
    // residual blocks, we must call
    // EvaluationCallback::PrepareForEvaluation(). Because this call
    // can be costly, we only call this if we actually encounter a
    // residual block with all constant parameter blocks.
    //
    // It is worth nothing that there is a minor inefficiency here,
    // that the iteration 0 of TrustRegionMinimizer will also cause
    // PrepareForEvaluation to be called on the same point, but with
    // evaluate_jacobians = true. We could try and optimize this here,
    // but given the rarity of this case, the additional complexity
    // and long range dependency is not worth it.
    if (need_to_call_prepare_for_evaluation) {
      constexpr bool kNewPoint = true;
      constexpr bool kDoNotEvaluateJacobians = false;
      evaluation_callback_->PrepareForEvaluation(kDoNotEvaluateJacobians,
                                                 kNewPoint);
      need_to_call_prepare_for_evaluation = false;
    }

    // The residual is constant and will be removed, so its cost is
    // added to the variable fixed_cost.
    double cost = 0.0;
    if (!residual_block->Evaluate(true,
                                  &cost,
                                  nullptr,
                                  nullptr,
                                  residual_block_evaluate_scratch.get())) {
      *error = StringPrintf(
          "Evaluation of the residual %d failed during "
          "removal of fixed residual blocks.",
          i);
      return false;
    }

    *fixed_cost += cost;
  }
  residual_blocks_.resize(num_active_residual_blocks);

  // Filter out unused or fixed parameter blocks.
  int num_active_parameter_blocks = 0;
  removed_parameter_blocks->clear();
  for (auto* parameter_block : parameter_blocks_) {
    if (parameter_block->index() == -1) {
      removed_parameter_blocks->push_back(
          parameter_block->mutable_user_state());
    } else {
      parameter_blocks_[num_active_parameter_blocks++] = parameter_block;
    }
  }
  parameter_blocks_.resize(num_active_parameter_blocks);

  if (!(((NumResidualBlocks() == 0) && (NumParameterBlocks() == 0)) ||
        ((NumResidualBlocks() != 0) && (NumParameterBlocks() != 0)))) {
    *error = "Congratulations, you found a bug in Ceres. Please report it.";
    return false;
  }

  return true;
}
