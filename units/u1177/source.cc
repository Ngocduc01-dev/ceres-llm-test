// u1177 – ceres::internal::Program::Plus
// Trích từ internal/ceres/program.cc, dòng 110–138 (chỉ để xem, không compile)

bool Program::Plus(const double* state,
                   const double* delta,
                   double* state_plus_delta,
                   ContextImpl* context,
                   int num_threads) const {
  std::atomic<bool> abort(false);
  auto* parameter_blocks = parameter_blocks_.data();
  ParallelFor(
      context,
      0,
      parameter_blocks_.size(),
      num_threads,
      [&abort, state, delta, state_plus_delta, parameter_blocks](int block_id) {
        if (abort) {
          return;
        }
        auto parameter_block = parameter_blocks[block_id];

        auto block_state = state + parameter_block->state_offset();
        auto block_delta = delta + parameter_block->delta_offset();
        auto block_state_plus_delta =
            state_plus_delta + parameter_block->state_offset();
        if (!parameter_block->Plus(
                block_state, block_delta, block_state_plus_delta)) {
          abort = true;
        }
      });
  return abort == false;
}
