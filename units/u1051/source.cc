// u1051 – ceres::SubsetManifold::MinusJacobian
// Trích từ internal/ceres/manifold.cc, dòng 252–263 (chỉ để xem, không compile)

bool SubsetManifold::MinusJacobian(const double* /*x*/,
                                   double* minus_jacobian) const {
  const int ambient_size = AmbientSize();
  MatrixRef m(minus_jacobian, tangent_size_, ambient_size);
  m.setZero();
  for (int c = 0, r = 0; c < ambient_size; ++c) {
    if (!constancy_mask_[c]) {
      m(r++, c) = 1.0;
    }
  }
  return true;
}
