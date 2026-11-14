// u0071 – ceres::Jet::Jet<T, N>
// Trích từ include/ceres/jet.h, dòng 239–241 (chỉ để xem, không compile)

  template <typename Derived>
  EIGEN_STRONG_INLINE Jet(const T& a, const Eigen::DenseBase<Derived>& v)
      : a(a), v(v) {}
