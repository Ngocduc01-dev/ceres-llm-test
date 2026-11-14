// u1050 – ceres::SubsetManifold::Plus
// Trích từ internal/ceres/manifold.cc, dòng 185–197 (chỉ để xem, không compile)

bool SubsetManifold::Plus(const double* x,
                          const double* delta,
                          double* x_plus_delta) const {
  const int ambient_size = AmbientSize();
  for (int i = 0, j = 0; i < ambient_size; ++i) {
    if (constancy_mask_[i]) {
      x_plus_delta[i] = x[i];
    } else {
      x_plus_delta[i] = x[i] + delta[j++];
    }
  }
  return true;
}
