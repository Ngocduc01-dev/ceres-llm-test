// u1013 – ceres::internal::ParallelInvokeState::ParallelInvokeState
// Trích từ internal/ceres/parallel_invoke.cc, dòng 65–75 (chỉ để xem, không compile)

ParallelInvokeState::ParallelInvokeState(int start,
                                         int end,
                                         int num_work_blocks)
    : start(start),
      end(end),
      num_work_blocks(num_work_blocks),
      base_block_size((end - start) / num_work_blocks),
      num_base_p1_sized_blocks((end - start) % num_work_blocks),
      block_id(0),
      thread_id(0),
      block_until_finished(num_work_blocks) {}
