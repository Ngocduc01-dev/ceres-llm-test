// u1410 – ceres::internal::LexicographicallyOrderResidualBlocks
// Trích từ internal/ceres/reorder_program.cc, dòng 254–335 (chỉ để xem, không compile)

bool LexicographicallyOrderResidualBlocks(
    const int size_of_first_elimination_group,
    Program* program,
    std::string* /*error*/) {
  CHECK_GE(size_of_first_elimination_group, 1)
      << "Congratulations, you found a Ceres bug! Please report this error "
      << "to the developers.";

  // Create a histogram of the number of residuals for each E block. There is an
  // extra bucket at the end to catch all non-eliminated F blocks.
  std::vector<int> residual_blocks_per_e_block(size_of_first_elimination_group +
                                               1);
  std::vector<ResidualBlock*>* residual_blocks =
      program->mutable_residual_blocks();
  std::vector<int> min_position_per_residual(residual_blocks->size());
  for (int i = 0; i < residual_blocks->size(); ++i) {
    ResidualBlock* residual_block = (*residual_blocks)[i];
    int position =
        MinParameterBlock(residual_block, size_of_first_elimination_group);
    min_position_per_residual[i] = position;
    DCHECK_LE(position, size_of_first_elimination_group);
    residual_blocks_per_e_block[position]++;
  }

  // Run a cumulative sum on the histogram, to obtain offsets to the start of
  // each histogram bucket (where each bucket is for the residuals for that
  // E-block).
  std::vector<int> offsets(size_of_first_elimination_group + 1);
  std::partial_sum(residual_blocks_per_e_block.begin(),
                   residual_blocks_per_e_block.end(),
                   offsets.begin());
  CHECK_EQ(offsets.back(), residual_blocks->size())
      << "Congratulations, you found a Ceres bug! Please report this error "
      << "to the developers.";

  CHECK(find(residual_blocks_per_e_block.begin(),
             residual_blocks_per_e_block.end() - 1,
             0) == residual_blocks_per_e_block.end() - 1)
      << "Congratulations, you found a Ceres bug! Please report this error "
      << "to the developers.";

  // Fill in each bucket with the residual blocks for its corresponding E block.
  // Each bucket is individually filled from the back of the bucket to the front
  // of the bucket. The filling order among the buckets is dictated by the
  // residual blocks. This loop uses the offsets as counters; subtracting one
  // from each offset as a residual block is placed in the bucket. When the
  // filling is finished, the offset pointers should have shifted down one
  // entry (this is verified below).
  std::vector<ResidualBlock*> reordered_residual_blocks(
      (*residual_blocks).size(), static_cast<ResidualBlock*>(nullptr));
  for (int i = 0; i < residual_blocks->size(); ++i) {
    int bucket = min_position_per_residual[i];

    // Decrement the cursor, which should now point at the next empty position.
    offsets[bucket]--;

    // Sanity.
    CHECK(reordered_residual_blocks[offsets[bucket]] == nullptr)
        << "Congratulations, you found a Ceres bug! Please report this error "
        << "to the developers.";

    reordered_residual_blocks[offsets[bucket]] = (*residual_blocks)[i];
  }

  // Sanity check #1: The difference in bucket offsets should match the
  // histogram sizes.
  for (int i = 0; i < size_of_first_elimination_group; ++i) {
    CHECK_EQ(residual_blocks_per_e_block[i], offsets[i + 1] - offsets[i])
        << "Congratulations, you found a Ceres bug! Please report this error "
        << "to the developers.";
  }
  // Sanity check #2: No nullptr's left behind.
  for (auto* residual_block : reordered_residual_blocks) {
    CHECK(residual_block != nullptr)
        << "Congratulations, you found a Ceres bug! Please report this error "
        << "to the developers.";
  }

  // Now that the residuals are collected by E block, swap them in place.
  swap(*program->mutable_residual_blocks(), reordered_residual_blocks);
  return true;
}
