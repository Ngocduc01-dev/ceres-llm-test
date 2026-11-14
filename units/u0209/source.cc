// u0209 – ceres::RotationMatrixToEulerAngles
// Trích từ include/ceres/rotation.h, dòng 557–560 (chỉ để xem, không compile)

template <typename EulerSystem, typename T>
inline void RotationMatrixToEulerAngles(const T* R, T* euler) {
  RotationMatrixToEulerAngles<EulerSystem>(RowMajorAdapter3x3(R), euler);
}
