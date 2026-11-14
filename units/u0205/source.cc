// u0205 – ceres::RotationMatrixToQuaternion
// Trích từ include/ceres/rotation.h, dòng 390–393 (chỉ để xem, không compile)

template <typename T>
void RotationMatrixToQuaternion(const T* R, T* quaternion) {
  RotationMatrixToQuaternion(ColumnMajorAdapter3x3(R), quaternion);
}
