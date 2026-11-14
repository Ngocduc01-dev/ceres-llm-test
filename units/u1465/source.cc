// u1465 – ceres::internal::ProblemImpl::InternalAddParameterBlock
// Trích từ internal/ceres/problem_impl.cc, dòng 122–174 (chỉ để xem, không compile)

ParameterBlock* ProblemImpl::InternalAddParameterBlock(double* values,
                                                       int size) {
  CHECK(values != nullptr) << "Null pointer passed to AddParameterBlock "
                           << "for a parameter with size " << size;

  // Ignore the request if there is a block for the given pointer already.
  auto it = parameter_block_map_.find(values);
  if (it != parameter_block_map_.end()) {
    if (!options_.disable_all_safety_checks) {
      int existing_size = it->second->Size();
      CHECK(size == existing_size)
          << "Tried adding a parameter block with the same double pointer, "
          << values << ", twice, but with different block sizes. Original "
          << "size was " << existing_size << " but new size is " << size;
    }
    return it->second;
  }

  if (!options_.disable_all_safety_checks) {
    // Before adding the parameter block, also check that it doesn't alias any
    // other parameter blocks.
    if (!parameter_block_map_.empty()) {
      auto lb = parameter_block_map_.lower_bound(values);

      // If lb is not the first block, check the previous block for aliasing.
      if (lb != parameter_block_map_.begin()) {
        auto previous = lb;
        --previous;
        CheckForNoAliasing(
            previous->first, previous->second->Size(), values, size);
      }

      // If lb is not off the end, check lb for aliasing.
      if (lb != parameter_block_map_.end()) {
        CheckForNoAliasing(lb->first, lb->second->Size(), values, size);
      }
    }
  }

  // Pass the index of the new parameter block as well to keep the index in
  // sync with the position of the parameter in the program's parameter vector.
  auto* new_parameter_block =
      new ParameterBlock(values, size, program_->parameter_blocks_.size());

  // For dynamic problems, add the list of dependent residual blocks, which is
  // empty to start.
  if (options_.enable_fast_removal) {
    new_parameter_block->EnableResidualBlockDependencies();
  }
  parameter_block_map_[values] = new_parameter_block;
  program_->parameter_blocks_.push_back(new_parameter_block);
  return new_parameter_block;
}
