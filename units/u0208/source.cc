// u0208 – ceres::EulerAnglesToRotation
// Trích từ include/ceres/rotation.h, dòng 496–499 (chỉ để xem, không compile)

template <typename EulerSystem, typename T>
inline void EulerAnglesToRotation(const T* euler, T* R) {
  EulerAnglesToRotation<EulerSystem>(euler, RowMajorAdapter3x3(R));
}
