// u0643 – ceres::RowMajorAdapter3x3
// Trích từ include/ceres/rotation.h, dòng 309–312 (chỉ để xem, không compile)

template <typename T>
MatrixAdapter<T, 3, 1> RowMajorAdapter3x3(T* pointer) {
  return MatrixAdapter<T, 3, 1>(pointer);
}
