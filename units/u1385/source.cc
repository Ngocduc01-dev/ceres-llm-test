// u1385 – ceres::internal::Program::MaxScratchDoublesNeededForEvaluate
// Trích từ internal/ceres/program.cc, dòng 510–519 (chỉ để xem, không compile)

int Program::MaxScratchDoublesNeededForEvaluate() const {
  // Compute the scratch space needed for evaluate.
  int max_scratch_bytes_for_evaluate = 0;
  for (auto* residual_block : residual_blocks_) {
    max_scratch_bytes_for_evaluate =
        std::max(max_scratch_bytes_for_evaluate,
                 residual_block->NumScratchDoublesForEvaluate());
  }
  return max_scratch_bytes_for_evaluate;
}
