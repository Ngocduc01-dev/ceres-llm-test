// u0698 – ceres::AngleAxisToRotationMatrix
// Trích từ include/ceres/rotation.h, dòng 453–494 (chỉ để xem, không compile)

template <typename T, int row_stride, int col_stride>
void AngleAxisToRotationMatrix(
    const T* angle_axis, const MatrixAdapter<T, row_stride, col_stride>& R) {
  using std::fpclassify;
  using std::hypot;
  static const T kOne = T(1.0);
  const T theta = hypot(angle_axis[0], angle_axis[1], angle_axis[2]);
  if (fpclassify(theta) != FP_ZERO) {
    // We want to be careful to only evaluate the square root if the
    // norm of the angle_axis vector is greater than zero. Otherwise
    // we get a division by zero.
    const T wx = angle_axis[0] / theta;
    const T wy = angle_axis[1] / theta;
    const T wz = angle_axis[2] / theta;

    const T costheta = cos(theta);
    const T sintheta = sin(theta);

    // clang-format off
    R(0, 0) =     costheta   + wx*wx*(kOne -    costheta);
    R(1, 0) =  wz*sintheta   + wx*wy*(kOne -    costheta);
    R(2, 0) = -wy*sintheta   + wx*wz*(kOne -    costheta);
    R(0, 1) =  wx*wy*(kOne - costheta)     - wz*sintheta;
    R(1, 1) =     costheta   + wy*wy*(kOne -    costheta);
    R(2, 1) =  wx*sintheta   + wy*wz*(kOne -    costheta);
    R(0, 2) =  wy*sintheta   + wx*wz*(kOne -    costheta);
    R(1, 2) = -wx*sintheta   + wy*wz*(kOne -    costheta);
    R(2, 2) =     costheta   + wz*wz*(kOne -    costheta);
    // clang-format on
  } else {
    // At zero, we switch to using the first order Taylor expansion.
    R(0, 0) = kOne;
    R(1, 0) = angle_axis[2];
    R(2, 0) = -angle_axis[1];
    R(0, 1) = -angle_axis[2];
    R(1, 1) = kOne;
    R(2, 1) = angle_axis[0];
    R(0, 2) = angle_axis[1];
    R(1, 2) = -angle_axis[0];
    R(2, 2) = kOne;
  }
}
