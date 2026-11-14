// u0853 – ceres::internal::Axpby
// Trích từ internal/ceres/eigen_vector_ops.h, dòng 66–74 (chỉ để xem, không compile)

inline void Axpby(double a,
                  const Vector& x,
                  double b,
                  const Vector& y,
                  Vector& z,
                  ContextImpl* context,
                  int num_threads) {
  ParallelAssign(context, num_threads, z, a * x + b * y);
}
