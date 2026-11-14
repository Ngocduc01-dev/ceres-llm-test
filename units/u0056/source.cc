// u0056 – ceres::internal::ApplyHouseholderVector
// Trích từ include/ceres/internal/householder_vector.h, dòng 84–90 (chỉ để xem, không compile)

template <typename XVectorType, typename Derived>
typename Derived::PlainObject ApplyHouseholderVector(
    const XVectorType& y,
    const Eigen::MatrixBase<Derived>& v,
    const typename Derived::Scalar& beta) {
  return (y - v * (beta * (v.transpose() * y)));
}
