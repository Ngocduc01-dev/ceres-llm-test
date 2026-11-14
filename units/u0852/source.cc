// u0852 – ceres::internal::SetZero
// Trích từ internal/ceres/eigen_vector_ops.h, dòng 63–65 (chỉ để xem, không compile)

inline void SetZero(Vector& x, ContextImpl* context, int num_threads) {
  ParallelSetZero(context, num_threads, x);
}
