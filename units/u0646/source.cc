// u0646 – ceres::QuaternionToScaledRotation
// Trích từ include/ceres/rotation.h, dòng 673–699 (chỉ để xem, không compile)

template <typename T, int row_stride, int col_stride>
inline void QuaternionToScaledRotation(
    const T q[4], const MatrixAdapter<T, row_stride, col_stride>& R) {
  // Make convenient names for elements of q.
  T a = q[0];
  T b = q[1];
  T c = q[2];
  T d = q[3];
  // This is not to eliminate common sub-expression, but to
  // make the lines shorter so that they fit in 80 columns!
  T aa = a * a;
  T ab = a * b;
  T ac = a * c;
  T ad = a * d;
  T bb = b * b;
  T bc = b * c;
  T bd = b * d;
  T cc = c * c;
  T cd = c * d;
  T dd = d * d;

  // clang-format off
  R(0, 0) = aa + bb - cc - dd; R(0, 1) = T(2) * (bc - ad);  R(0, 2) = T(2) * (ac + bd);
  R(1, 0) = T(2) * (ad + bc);  R(1, 1) = aa - bb + cc - dd; R(1, 2) = T(2) * (cd - ab);
  R(2, 0) = T(2) * (bd - ac);  R(2, 1) = T(2) * (ab + cd);  R(2, 2) = aa - bb - cc + dd;
  // clang-format on
}
