// u0855 – ceres::internal::Copy
// Trích từ internal/ceres/eigen_vector_ops.h, dòng 96–101 (chỉ để xem, không compile)

inline void Copy(const Vector& from,
                 Vector& to,
                 ContextImpl* context,
                 int num_threads) {
  ParallelAssign(context, num_threads, to, from);
}
