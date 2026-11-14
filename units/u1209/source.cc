// u1209 – ceres::internal::ParallelInvoke
// Trích từ internal/ceres/parallel_invoke.h, dòng 164–268 (chỉ để xem, không compile)

template <typename F>
void ParallelInvoke(ContextImpl* context,
                    int start,
                    int end,
                    int num_threads,
                    F&& function,
                    int min_block_size) {
  CHECK(context != nullptr);

  // Maximal number of work items scheduled for a single thread
  //  - Lower number of work items results in larger runtimes on unequal tasks
  //  - Higher number of work items results in larger losses for synchronization
  constexpr int kWorkBlocksPerThread = 4;

  // Interval [start, end) is being split into
  // num_threads * kWorkBlocksPerThread contiguous disjoint blocks.
  //
  // In order to avoid creating empty blocks of work, we need to limit
  // number of work blocks by a total number of indices.
  const int num_work_blocks = std::min((end - start) / min_block_size,
                                       num_threads * kWorkBlocksPerThread);

  // We use a std::shared_ptr because the main thread can finish all
  // the work before the tasks have been popped off the queue.  So the
  // shared state needs to exist for the duration of all the tasks.
  auto shared_state =
      std::make_shared<ParallelInvokeState>(start, end, num_work_blocks);

  // A function which tries to schedule another task in the thread pool and
  // perform several chunks of work. Function expects itself as the argument in
  // order to schedule next task in the thread pool.
  auto task = [context, shared_state, num_threads, &function](auto& task_copy) {
    int num_jobs_finished = 0;
    const int thread_id = shared_state->thread_id.fetch_add(1);
    // In order to avoid dead-locks in nested parallel for loops, task() will be
    // invoked num_threads + 1 times:
    //  - num_threads times via enqueueing task into thread pool
    //  - one more time in the main thread
    //  Tasks enqueued to thread pool might take some time before execution, and
    //  the last task being executed will be terminated here in order to avoid
    //  having more than num_threads active threads
    if (thread_id >= num_threads) return;
    const int num_work_blocks = shared_state->num_work_blocks;
    if (thread_id + 1 < num_threads &&
        shared_state->block_id < num_work_blocks) {
      // Add another thread to the thread pool.
      // Note we are taking the task as value so the copy of shared_state shared
      // pointer (captured by value at declaration of task lambda-function) is
      // copied and the ref count is increased. This is to prevent it from being
      // deleted when the main thread finishes all the work and exits before the
      // threads finish.
      context->thread_pool.AddTask([task_copy]() { task_copy(task_copy); });
    }

    const int start = shared_state->start;
    const int base_block_size = shared_state->base_block_size;
    const int num_base_p1_sized_blocks = shared_state->num_base_p1_sized_blocks;

    while (true) {
      // Get the next available chunk of work to be performed. If there is no
      // work, return.
      int block_id = shared_state->block_id.fetch_add(1);
      if (block_id >= num_work_blocks) {
        break;
      }
      ++num_jobs_finished;

      // For-loop interval [start, end) was split into num_work_blocks,
      // with num_base_p1_sized_blocks of size base_block_size + 1 and remaining
      // num_work_blocks - num_base_p1_sized_blocks of size base_block_size
      //
      // Then, start index of the block #block_id is given by a total
      // length of preceeding blocks:
      //  * Total length of preceeding blocks of size base_block_size + 1:
      //     min(block_id, num_base_p1_sized_blocks) * (base_block_size + 1)
      //
      //  * Total length of preceeding blocks of size base_block_size:
      //     (block_id - min(block_id, num_base_p1_sized_blocks)) *
      //     base_block_size
      //
      // Simplifying sum of those quantities yields a following
      // expression for start index of the block #block_id
      const int curr_start = start + block_id * base_block_size +
                             std::min(block_id, num_base_p1_sized_blocks);
      // First num_base_p1_sized_blocks have size base_block_size + 1
      //
      // Note that it is guaranteed that all blocks are within
      // [start, end) interval
      const int curr_end = curr_start + base_block_size +
                           (block_id < num_base_p1_sized_blocks ? 1 : 0);
      // Perform each task in current block
      const auto range = std::make_tuple(curr_start, curr_end);
      InvokeOnSegment(thread_id, range, function);
    }
    shared_state->block_until_finished.Finished(num_jobs_finished);
  };

  // Start scheduling threads and doing work. We might end up with less threads
  // scheduled than expected, if scheduling overhead is larger than the amount
  // of work to be done.
  task(task);

  // Wait until all tasks have finished.
  shared_state->block_until_finished.Block();
}
