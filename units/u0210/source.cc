// u0210 – ceres::EulerAnglesToRotationMatrix
// Trích từ include/ceres/rotation.h, dòng 631–636 (chỉ để xem, không compile)

template <typename T>
inline void EulerAnglesToRotationMatrix(const T* euler,
                                        const int row_stride_parameter,
                                        T* R) {
  EulerAnglesToRotationMatrix(euler, RowMajorAdapter3x3(R));
}
