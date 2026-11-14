// u0644 – ceres::RotationMatrixToAngleAxis
// Trích từ include/ceres/rotation.h, dòng 439–446 (chỉ để xem, không compile)

template <typename T, int row_stride, int col_stride>
void RotationMatrixToAngleAxis(
    const MatrixAdapter<const T, row_stride, col_stride>& R, T* angle_axis) {
  T quaternion[4];
  RotationMatrixToQuaternion(R, quaternion);
  QuaternionToAngleAxis(quaternion, angle_axis);
  return;
}
