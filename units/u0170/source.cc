// u0170 – ceres::LineManifold::Minus
// Trích từ include/ceres/line_manifold.h, dòng 240–270 (chỉ để xem, không compile)

template <int AmbientSpaceDimension>
bool LineManifold<AmbientSpaceDimension>::Minus(const double* y_ptr,
                                                const double* x_ptr,
                                                double* y_minus_x) const {
  Eigen::Map<const AmbientVector> y_o(y_ptr, size_);
  Eigen::Map<const AmbientVector> y_d(y_ptr + size_, size_);
  Eigen::Map<const AmbientVector> x_o(x_ptr, size_);
  Eigen::Map<const AmbientVector> x_d(x_ptr + size_, size_);

  Eigen::Map<TangentVector> y_minus_x_o(y_minus_x, size_ - 1);
  Eigen::Map<TangentVector> y_minus_x_d(y_minus_x + size_ - 1, size_ - 1);

  AmbientVector v(size_);
  double beta;

  // NOTE: The explicit template arguments are needed here because
  // ComputeHouseholderVector is templated and some versions of MSVC
  // have trouble deducing the type of v automatically.
  internal::ComputeHouseholderVector<Eigen::Map<const AmbientVector>,
                                     double,
                                     AmbientSpaceDimension>(x_d, &v, &beta);

  internal::ComputeSphereManifoldMinus(v, beta, x_d, y_d, &y_minus_x_d);

  AmbientVector delta_o = y_o - x_o;
  const AmbientVector h_delta_o =
      internal::ApplyHouseholderVector(delta_o, v, beta);
  y_minus_x_o = h_delta_o.template head<TangentSpaceDimension>(size_ - 1);

  return true;
}
