// u0909 – ceres::internal::ParallelAssign
// Trích từ internal/ceres/parallel_vector_ops.h, dòng 55–74 (chỉ để xem, không compile)

template <typename LhsExpression, typename RhsExpression>
void ParallelAssign(ContextImpl* context,
                    int num_threads,
                    LhsExpression& lhs,
                    const RhsExpression& rhs) {
  static_assert(LhsExpression::ColsAtCompileTime == 1);
  static_assert(RhsExpression::ColsAtCompileTime == 1);
  CHECK_EQ(lhs.rows(), rhs.rows());
  const int num_rows = lhs.rows();
  ParallelFor(
      context,
      0,
      num_rows,
      num_threads,
      [&lhs, &rhs](const std::tuple<int, int>& range) {
        auto [start, end] = range;
        lhs.segment(start, end - start) = rhs.segment(start, end - start);
      },
      kMinBlockSizeParallelVectorOps);
}
