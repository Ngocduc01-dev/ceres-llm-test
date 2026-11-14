// u1407 – ceres::internal::ProblemImpl::EvaluateResidualBlock
// Trích từ internal/ceres/problem_impl.cc, dòng 748–784 (chỉ để xem, không compile)

bool ProblemImpl::EvaluateResidualBlock(ResidualBlock* residual_block,
                                        bool apply_loss_function,
                                        bool new_point,
                                        double* cost,
                                        double* residuals,
                                        double** jacobians) const {
  auto evaluation_callback = program_->mutable_evaluation_callback();
  if (evaluation_callback) {
    evaluation_callback->PrepareForEvaluation(jacobians != nullptr, new_point);
  }

  ParameterBlock* const* parameter_blocks = residual_block->parameter_blocks();
  const int num_parameter_blocks = residual_block->NumParameterBlocks();
  for (int i = 0; i < num_parameter_blocks; ++i) {
    ParameterBlock* parameter_block = parameter_blocks[i];
    if (parameter_block->IsConstant()) {
      if (jacobians != nullptr && jacobians[i] != nullptr) {
        LOG(ERROR) << "Jacobian requested for parameter block : " << i
                   << ". But the parameter block is marked constant.";
        return false;
      }
    } else {
      CHECK(parameter_block->SetState(parameter_block->user_state()))
          << "Congratulations, you found a Ceres bug! Please report this error "
          << "to the developers.";
    }
  }

  double dummy_cost = 0.0;
  FixedArray<double, 32> scratch(
      residual_block->NumScratchDoublesForEvaluate());
  return residual_block->Evaluate(apply_loss_function,
                                  cost ? cost : &dummy_cost,
                                  residuals,
                                  jacobians,
                                  scratch.data());
}
