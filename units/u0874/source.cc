// u0874 – ceres::internal::ParallelSetZero
// Trích từ internal/ceres/parallel_vector_ops.cc, dòng 38–52 (chỉ để xem, không compile)

void ParallelSetZero(ContextImpl* context,
                     int num_threads,
                     double* values,
                     int num_values) {
  ParallelFor(
      context,
      0,
      num_values,
      num_threads,
      [values](std::tuple<int, int> range) {
        auto [start, end] = range;
        std::fill(values + start, values + end, 0.);
      },
      kMinBlockSizeParallelVectorOps);
}
