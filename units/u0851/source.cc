// u0851 – ceres::internal::Norm
// Trích từ internal/ceres/eigen_vector_ops.h, dòng 46–62 (chỉ để xem, không compile)

template <typename Derived>
inline double Norm(const Eigen::DenseBase<Derived>& x,
                   ContextImpl* context,
                   int num_threads) {
  FixedArray<double> norms(num_threads, 0.);
  ParallelFor(
      context,
      0,
      x.rows(),
      num_threads,
      [&x, &norms](int thread_id, std::tuple<int, int> range) {
        auto [start, end] = range;
        norms[thread_id] += x.segment(start, end - start).squaredNorm();
      },
      kMinBlockSizeParallelVectorOps);
  return std::sqrt(std::accumulate(norms.begin(), norms.end(), 0.));
}
