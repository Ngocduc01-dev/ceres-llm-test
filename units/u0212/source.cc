// u0212 – ceres::QuaternionToRotation
// Trích từ include/ceres/rotation.h, dòng 701–704 (chỉ để xem, không compile)

template <typename T>
inline void QuaternionToRotation(const T q[4], T R[3 * 3]) {
  QuaternionToRotation(q, RowMajorAdapter3x3(R));
}
