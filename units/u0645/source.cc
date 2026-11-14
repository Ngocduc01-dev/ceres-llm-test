// u0645 – ceres::EulerAnglesToRotationMatrix
// Trích từ include/ceres/rotation.h, dòng 638–666 (chỉ để xem, không compile)

template <typename T, int row_stride, int col_stride>
void EulerAnglesToRotationMatrix(
    const T* euler, const MatrixAdapter<T, row_stride, col_stride>& R) {
  const double kPi = 3.14159265358979323846;
  const T degrees_to_radians(kPi / 180.0);

  const T pitch(euler[0] * degrees_to_radians);
  const T roll(euler[1] * degrees_to_radians);
  const T yaw(euler[2] * degrees_to_radians);

  const T c1 = cos(yaw);
  const T s1 = sin(yaw);
  const T c2 = cos(roll);
  const T s2 = sin(roll);
  const T c3 = cos(pitch);
  const T s3 = sin(pitch);

  R(0, 0) = c1 * c2;
  R(0, 1) = -s1 * c3 + c1 * s2 * s3;
  R(0, 2) = s1 * s3 + c1 * s2 * c3;

  R(1, 0) = s1 * c2;
  R(1, 1) = c1 * c3 + s1 * s2 * s3;
  R(1, 2) = -c1 * s3 + s1 * s2 * c3;

  R(2, 0) = -s2;
  R(2, 1) = c2 * s3;
  R(2, 2) = c2 * c3;
}
