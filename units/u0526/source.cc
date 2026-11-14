// u0526 – ceres::internal::InvertPSDMatrix
// Trích từ internal/ceres/invert_psd_matrix.h, dòng 49–73 (chỉ để xem, không compile)

template <int kSize>
typename EigenTypes<kSize, kSize>::Matrix InvertPSDMatrix(
    const bool assume_full_rank,
    const typename EigenTypes<kSize, kSize>::Matrix& m) {
  using MType = typename EigenTypes<kSize, kSize>::Matrix;
  const int size = m.rows();

  // If the matrix can be assumed to be full rank, then if it is small
  // (< 5) and fixed size, use Eigen's optimized inverse()
  // implementation.
  //
  // https://eigen.tuxfamily.org/dox/group__TutorialLinearAlgebra.html#title3
  if (assume_full_rank) {
    if (kSize > 0 && kSize < 5) {
      return m.inverse();
    }
    return m.template selfadjointView<Eigen::Upper>().llt().solve(
        MType::Identity(size, size));
  }

  // For a thin SVD the number of columns of the matrix need to be dynamic.
  using SVDMType = typename EigenTypes<kSize, Eigen::Dynamic>::Matrix;
  Eigen::JacobiSVD<SVDMType> svd(m, Eigen::ComputeThinU | Eigen::ComputeThinV);
  return svd.solve(MType::Identity(size, size));
}
