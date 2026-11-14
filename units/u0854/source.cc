// u0854 – ceres::internal::Dot
// Trích từ internal/ceres/eigen_vector_ops.h, dòng 75–95 (chỉ để xem, không compile)

template <typename VectorLikeX, typename VectorLikeY>
inline double Dot(const VectorLikeX& x,
                  const VectorLikeY& y,
                  ContextImpl* context,
                  int num_threads) {
  FixedArray<double> dots(num_threads, 0.);
  ParallelFor(
      context,
      0,
      x.rows(),
      num_threads,
      [&x, &y, &dots](int thread_id, std::tuple<int, int> range) {
        auto [start, end] = range;
        const int block_size = end - start;
        const auto& x_block = x.segment(start, block_size);
        const auto& y_block = y.segment(start, block_size);
        dots[thread_id] += x_block.dot(y_block);
      },
      kMinBlockSizeParallelVectorOps);
  return std::accumulate(dots.begin(), dots.end(), 0.);
}
