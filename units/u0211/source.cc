// u0211 – ceres::QuaternionToScaledRotation
// Trích từ include/ceres/rotation.h, dòng 668–671 (chỉ để xem, không compile)

template <typename T>
inline void QuaternionToScaledRotation(const T q[4], T R[3 * 3]) {
  QuaternionToScaledRotation(q, RowMajorAdapter3x3(R));
}
