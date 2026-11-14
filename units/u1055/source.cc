// u1055 – ceres::SubsetManifold::Minus
// Trích từ internal/ceres/manifold.cc, dòng 236–250 (chỉ để xem, không compile)

bool SubsetManifold::Minus(const double* y,
                           const double* x,
                           double* y_minus_x) const {
  if (tangent_size_ == 0) {
    return true;
  }

  const int ambient_size = AmbientSize();
  for (int i = 0, j = 0; i < ambient_size; ++i) {
    if (!constancy_mask_[i]) {
      y_minus_x[j++] = y[i] - x[i];
    }
  }
  return true;
}
