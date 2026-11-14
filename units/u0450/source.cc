// u0450 – ceres::internal::ComputeSphereManifoldMinusJacobian
// Trích từ include/ceres/internal/sphere_manifold_functions.h, dòng 133–159 (chỉ để xem, không compile)

template <typename VT, typename JacobianT>
inline void ComputeSphereManifoldMinusJacobian(const VT& x,
                                               JacobianT* jacobian) {
  constexpr int AmbientSpaceDim = VT::RowsAtCompileTime;
  using AmbientVector = Eigen::Matrix<double, AmbientSpaceDim, 1>;
  const int ambient_size = x.size();
  const int tangent_size = x.size() - 1;

  AmbientVector v(ambient_size);
  double beta;

  // NOTE: The explicit template arguments are needed here because
  // ComputeHouseholderVector is templated and some versions of MSVC
  // have trouble deducing the type of v automatically.
  ComputeHouseholderVector<VT, double, AmbientSpaceDim>(x, &v, &beta);

  // The Jacobian is equal to J = H.leftCols(size_ - 1) where H is the
  // Householder matrix (H = I - beta * v * v').
  for (int i = 0; i < tangent_size; ++i) {
    // NOTE: The transpose is used for correctness (the product is expected to
    // be a row vector), although here there seems to be no difference between
    // transposing or not for Eigen (possibly a compile-time auto fix).
    (*jacobian).row(i) = -beta * v(i) * v.transpose();
    (*jacobian)(i, i) += 1.0;
  }
  (*jacobian) /= x.norm();
}
