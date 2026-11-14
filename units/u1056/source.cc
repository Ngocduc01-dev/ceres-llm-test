// u1056 – ceres::SubsetManifold::RightMultiplyByPlusJacobian
// Trích từ internal/ceres/manifold.cc, dòng 216–234 (chỉ để xem, không compile)

bool SubsetManifold::RightMultiplyByPlusJacobian(const double* /*x*/,
                                                 const int num_rows,
                                                 const double* ambient_matrix,
                                                 double* tangent_matrix) const {
  if (tangent_size_ == 0) {
    return true;
  }

  const int ambient_size = AmbientSize();
  for (int r = 0; r < num_rows; ++r) {
    for (int idx = 0, c = 0; idx < ambient_size; ++idx) {
      if (!constancy_mask_[idx]) {
        tangent_matrix[r * tangent_size_ + c++] =
            ambient_matrix[r * ambient_size + idx];
      }
    }
  }
  return true;
}
