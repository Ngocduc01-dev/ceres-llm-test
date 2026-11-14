// u1269 – ceres::internal::ProblemImpl::~ProblemImpl
// Trích từ internal/ceres/problem_impl.cc, dòng 239–265 (chỉ để xem, không compile)

ProblemImpl::~ProblemImpl() {
  STLDeleteContainerPointers(program_->residual_blocks_.begin(),
                             program_->residual_blocks_.end());

  if (options_.cost_function_ownership == TAKE_OWNERSHIP) {
    STLDeleteContainerPairFirstPointers(cost_function_ref_count_.begin(),
                                        cost_function_ref_count_.end());
  }

  if (options_.loss_function_ownership == TAKE_OWNERSHIP) {
    STLDeleteContainerPairFirstPointers(loss_function_ref_count_.begin(),
                                        loss_function_ref_count_.end());
  }

  // Collect the unique parameterizations and delete the parameters.
  for (auto* parameter_block : program_->parameter_blocks_) {
    DeleteBlock(parameter_block);
  }

  // Delete the owned manifolds.
  STLDeleteUniqueContainerPointers(manifolds_to_delete_.begin(),
                                   manifolds_to_delete_.end());

  if (context_impl_owned_) {
    delete context_impl_;
  }
}
