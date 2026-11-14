// u1500 – ceres::internal::ProblemImpl::RemoveResidualBlock
// Trích từ internal/ceres/problem_impl.cc, dòng 405–433 (chỉ để xem, không compile)

void ProblemImpl::RemoveResidualBlock(ResidualBlock* residual_block) {
  CHECK(residual_block != nullptr);

  // Verify that residual_block identifies a residual in the current problem.
  const std::string residual_not_found_message = StringPrintf(
      "Residual block to remove: %p not found. This usually means "
      "one of three things have happened:\n"
      " 1) residual_block is uninitialised and points to a random "
      "area in memory.\n"
      " 2) residual_block represented a residual that was added to"
      " the problem, but referred to a parameter block which has "
      "since been removed, which removes all residuals which "
      "depend on that parameter block, and was thus removed.\n"
      " 3) residual_block referred to a residual that has already "
      "been removed from the problem (by the user).",
      residual_block);
  if (options_.enable_fast_removal) {
    CHECK(residual_block_set_.find(residual_block) != residual_block_set_.end())
        << residual_not_found_message;
  } else {
    // Perform a full search over all current residuals.
    CHECK(std::find(program_->residual_blocks().begin(),
                    program_->residual_blocks().end(),
                    residual_block) != program_->residual_blocks().end())
        << residual_not_found_message;
  }

  InternalRemoveResidualBlock(residual_block);
}
