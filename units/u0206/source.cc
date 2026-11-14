// u0206 – ceres::RotationMatrixToAngleAxis
// Trích từ include/ceres/rotation.h, dòng 434–437 (chỉ để xem, không compile)

template <typename T>
inline void RotationMatrixToAngleAxis(const T* R, T* angle_axis) {
  RotationMatrixToAngleAxis(ColumnMajorAdapter3x3(R), angle_axis);
}
