// u1467 – ceres::internal::StateUpdatingCallback::operator()
// Trích từ internal/ceres/callbacks.cc, dòng 49–54 (chỉ để xem, không compile)

CallbackReturnType StateUpdatingCallback::operator()(
    const IterationSummary& /*summary*/) {
  program_->StateVectorToParameterBlocks(parameters_);
  program_->CopyParameterBlockStateToUserState();
  return SOLVER_CONTINUE;
}
