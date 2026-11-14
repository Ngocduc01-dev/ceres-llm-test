// u0438 – ceres::AutoDiffManifold::MinusJacobian
// Trích từ include/ceres/autodiff_manifold.h, dòng 234–255 (chỉ để xem, không compile)

template <typename Functor, int kAmbientSize, int kTangentSize>
bool AutoDiffManifold<Functor, kAmbientSize, kTangentSize>::MinusJacobian(
    const double* x, double* jacobian) const {
  double y_minus_x[kTangentSize];
  for (int i = 0; i < kTangentSize; ++i) {
    y_minus_x[i] = 0.0;
  }

  const double* parameter_ptrs[2] = {x, x};

  // MinusJacobian is D_1 Minus(x,x), so we only need to compute the Jacobian
  // w.r.t. the first argument.
  double* jacobian_ptrs[2] = {jacobian, nullptr};
  return internal::AutoDifferentiate<
      kTangentSize,
      internal::StaticParameterDims<kAmbientSize, kAmbientSize>>(
      internal::MinusWrapper<Functor>(*functor_),
      parameter_ptrs,
      kTangentSize,
      y_minus_x,
      jacobian_ptrs);
}
