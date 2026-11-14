// u0207 – ceres::AngleAxisToRotationMatrix
// Trích từ include/ceres/rotation.h, dòng 448–451 (chỉ để xem, không compile)

template <typename T>
inline void AngleAxisToRotationMatrix(const T* angle_axis, T* R) {
  AngleAxisToRotationMatrix(angle_axis, ColumnMajorAdapter3x3(R));
}
