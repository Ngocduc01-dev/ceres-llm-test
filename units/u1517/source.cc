// u1517 – ceres::internal::ProblemImpl::AddResidualBlock
// Trích từ internal/ceres/problem_impl.cc, dòng 267–356 (chỉ để xem, không compile)

ResidualBlockId ProblemImpl::AddResidualBlock(
    CostFunction* cost_function,
    LossFunction* loss_function,
    double* const* const parameter_blocks,
    int num_parameter_blocks) {
  CHECK(cost_function != nullptr);
  CHECK_EQ(num_parameter_blocks, cost_function->parameter_block_sizes().size());

  // Check the sizes match.
  const std::vector<int32_t>& parameter_block_sizes =
      cost_function->parameter_block_sizes();

  if (!options_.disable_all_safety_checks) {
    CHECK_EQ(parameter_block_sizes.size(), num_parameter_blocks)
        << "Number of blocks input is different than the number of blocks "
        << "that the cost function expects.";

    // Check for duplicate parameter blocks.
    std::vector<double*> sorted_parameter_blocks(
        parameter_blocks, parameter_blocks + num_parameter_blocks);
    sort(sorted_parameter_blocks.begin(), sorted_parameter_blocks.end());
    const bool has_duplicate_items =
        (std::adjacent_find(sorted_parameter_blocks.begin(),
                            sorted_parameter_blocks.end()) !=
         sorted_parameter_blocks.end());
    if (has_duplicate_items) {
      std::string blocks;
      for (int i = 0; i < num_parameter_blocks; ++i) {
        blocks += StringPrintf(" %p ", parameter_blocks[i]);
      }

      LOG(FATAL) << "Duplicate parameter blocks in a residual parameter "
                 << "are not allowed. Parameter block pointers: [" << blocks
                 << "]";
    }
  }

  // Add parameter blocks and convert the double*'s to parameter blocks.
  std::vector<ParameterBlock*> parameter_block_ptrs(num_parameter_blocks);
  for (int i = 0; i < num_parameter_blocks; ++i) {
    parameter_block_ptrs[i] = InternalAddParameterBlock(
        parameter_blocks[i], parameter_block_sizes[i]);
  }

  if (!options_.disable_all_safety_checks) {
    // Check that the block sizes match the block sizes expected by the
    // cost_function.
    for (int i = 0; i < parameter_block_ptrs.size(); ++i) {
      CHECK_EQ(cost_function->parameter_block_sizes()[i],
               parameter_block_ptrs[i]->Size())
          << "The cost function expects parameter block " << i << " of size "
          << cost_function->parameter_block_sizes()[i]
          << " but was given a block of size "
          << parameter_block_ptrs[i]->Size();
    }
  }

  auto* new_residual_block =
      new ResidualBlock(cost_function,
                        loss_function,
                        parameter_block_ptrs,
                        program_->residual_blocks_.size());

  // Add dependencies on the residual to the parameter blocks.
  if (options_.enable_fast_removal) {
    for (int i = 0; i < num_parameter_blocks; ++i) {
      parameter_block_ptrs[i]->AddResidualBlock(new_residual_block);
    }
  }

  program_->residual_blocks_.push_back(new_residual_block);

  if (options_.enable_fast_removal) {
    residual_block_set_.insert(new_residual_block);
  }

  if (options_.cost_function_ownership == TAKE_OWNERSHIP) {
    // Increment the reference count, creating an entry in the table if
    // needed. Note: C++ maps guarantee that new entries have default
    // constructed values; this implies integers are zero initialized.
    ++cost_function_ref_count_[cost_function];
  }

  if (options_.loss_function_ownership == TAKE_OWNERSHIP &&
      loss_function != nullptr) {
    ++loss_function_ref_count_[loss_function];
  }

  return new_residual_block;
}
