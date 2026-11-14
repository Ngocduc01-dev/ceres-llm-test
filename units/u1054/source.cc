// u1054 – ceres::SubsetManifold::PlusJacobian
// Trích từ internal/ceres/manifold.cc, dòng 199–214 (chỉ để xem, không compile)

bool SubsetManifold::PlusJacobian(const double* /*x*/,
                                  double* plus_jacobian) const {
  if (tangent_size_ == 0) {
    return true;
  }

  const int ambient_size = AmbientSize();
  MatrixRef m(plus_jacobian, ambient_size, tangent_size_);
  m.setZero();
  for (int r = 0, c = 0; r < ambient_size; ++r) {
    if (!constancy_mask_[r]) {
      m(r, c++) = 1.0;
    }
  }
  return true;
}
