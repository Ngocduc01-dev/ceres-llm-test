// u0875 – ceres::internal::ParallelSetZero
// Trích từ internal/ceres/parallel_vector_ops.h, dòng 77–82 (chỉ để xem, không compile)

template <typename VectorType>
void ParallelSetZero(ContextImpl* context,
                     int num_threads,
                     VectorType& vector) {
  ParallelSetZero(context, num_threads, vector.data(), vector.rows());
}
