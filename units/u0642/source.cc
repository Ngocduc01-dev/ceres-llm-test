// u0642 – ceres::ColumnMajorAdapter3x3
// Trích từ include/ceres/rotation.h, dòng 304–307 (chỉ để xem, không compile)

template <typename T>
MatrixAdapter<T, 1, 3> ColumnMajorAdapter3x3(T* pointer) {
  return MatrixAdapter<T, 1, 3>(pointer);
}
