// u0520 – ceres::LineManifold::Plus
// Trích từ include/ceres/line_manifold.h, dòng 141–216 (chỉ để xem, không compile)

template <int AmbientSpaceDimension>
bool LineManifold<AmbientSpaceDimension>::Plus(const double* x_ptr,
                                               const double* delta_ptr,
                                               double* x_plus_delta_ptr) const {
  // We seek a box plus operator of the form
  //
  //   [o*, d*] = Plus([o, d], [delta_o, delta_d])
  //
  // where o is the origin point, d is the direction vector, delta_o is
  // the delta of the origin point and delta_d the delta of the direction and
  // o* and d* is the updated origin point and direction.
  //
  // We separate the Plus operator into the origin point and directional part
  //   d* = Plus_d(d, delta_d)
  //   o* = Plus_o(o, d, delta_o)
  //
  // The direction update function Plus_d is the same as as the SphereManifold:
  //
  //   d* = H_{v(d)} [sinc(|delta_d|) delta_d, cos(|delta_d|)]^T
  //
  // where H is the householder matrix
  //   H_{v} = I - (2 / |v|^2) v v^T
  // and
  //   v(d) = d - sign(d_n) |d| e_n.
  //
  // The origin point update function Plus_o is defined as
  //
  //   o* = o + H_{v(d)} [delta_o, 0]^T.

  Eigen::Map<const AmbientVector> o(x_ptr, size_);
  Eigen::Map<const AmbientVector> d(x_ptr + size_, size_);

  Eigen::Map<const TangentVector> delta_o(delta_ptr, size_ - 1);
  Eigen::Map<const TangentVector> delta_d(delta_ptr + size_ - 1, size_ - 1);
  Eigen::Map<AmbientVector> o_plus_delta(x_plus_delta_ptr, size_);
  Eigen::Map<AmbientVector> d_plus_delta(x_plus_delta_ptr + size_, size_);

  const double norm_delta_d = delta_d.norm();

  o_plus_delta = o;

  // Shortcut for zero delta direction.
  if (norm_delta_d == 0.0) {
    d_plus_delta = d;

    if (delta_o.isZero(0.0)) {
      return true;
    }
  }

  // Calculate the householder transformation which is needed for f_d and f_o.
  AmbientVector v(size_);
  double beta;

  // NOTE: The explicit template arguments are needed here because
  // ComputeHouseholderVector is templated and some versions of MSVC
  // have trouble deducing the type of v automatically.
  internal::ComputeHouseholderVector<Eigen::Map<const AmbientVector>,
                                     double,
                                     AmbientSpaceDimension>(d, &v, &beta);

  if (norm_delta_d != 0.0) {
    internal::ComputeSphereManifoldPlus(
        v, beta, d, delta_d, norm_delta_d, &d_plus_delta);
  }

  // The null space is in the direction of the line, so the tangent space is
  // perpendicular to the line direction. This is achieved by using the
  // householder matrix of the direction and allow only movements
  // perpendicular to e_n.
  AmbientVector y(size_);
  y << delta_o, 0;
  o_plus_delta += internal::ApplyHouseholderVector(y, v, beta);

  return true;
}
