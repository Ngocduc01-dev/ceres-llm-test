// u0493 – ceres::AutoDiffManifold::PlusJacobian
// Trích từ include/ceres/autodiff_manifold.h, dòng 206–232 (chỉ để xem, không compile)

template <typename Functor, int kAmbientSize, int kTangentSize>
bool AutoDiffManifold<Functor, kAmbientSize, kTangentSize>::PlusJacobian(
    const double* x, double* jacobian) const {
  double zero_delta[kTangentSize];
  for (int i = 0; i < kTangentSize; ++i) {
    zero_delta[i] = 0.0;
  }

  double x_plus_delta[kAmbientSize];
  for (int i = 0; i < kAmbientSize; ++i) {
    x_plus_delta[i] = 0.0;
  }

  const double* parameter_ptrs[2] = {x, zero_delta};

  // PlusJacobian is D_2 Plus(x,0) so we only need to compute the Jacobian
  // w.r.t. the second argument.
  double* jacobian_ptrs[2] = {nullptr, jacobian};
  return internal::AutoDifferentiate<
      kAmbientSize,
      internal::StaticParameterDims<kAmbientSize, kTangentSize>>(
      internal::PlusWrapper<Functor>(*functor_),
      parameter_ptrs,
      kAmbientSize,
      x_plus_delta,
      jacobian_ptrs);
}
