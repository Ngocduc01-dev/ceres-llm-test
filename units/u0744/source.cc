// u0744 – ceres::RotationMatrixToQuaternion
// Trích từ include/ceres/rotation.h, dòng 397–427 (chỉ để xem, không compile)

template <typename T, int row_stride, int col_stride>
void RotationMatrixToQuaternion(
    const MatrixAdapter<const T, row_stride, col_stride>& R, T* quaternion) {
  const T trace = R(0, 0) + R(1, 1) + R(2, 2);
  if (trace >= 0.0) {
    T t = sqrt(trace + T(1.0));
    quaternion[0] = T(0.5) * t;
    t = T(0.5) / t;
    quaternion[1] = (R(2, 1) - R(1, 2)) * t;
    quaternion[2] = (R(0, 2) - R(2, 0)) * t;
    quaternion[3] = (R(1, 0) - R(0, 1)) * t;
  } else {
    int i = 0;
    if (R(1, 1) > R(0, 0)) {
      i = 1;
    }

    if (R(2, 2) > R(i, i)) {
      i = 2;
    }

    const int j = (i + 1) % 3;
    const int k = (j + 1) % 3;
    T t = sqrt(R(i, i) - R(j, j) - R(k, k) + T(1.0));
    quaternion[i + 1] = T(0.5) * t;
    t = T(0.5) / t;
    quaternion[0] = (R(k, j) - R(j, k)) * t;
    quaternion[j + 1] = (R(j, i) + R(i, j)) * t;
    quaternion[k + 1] = (R(k, i) + R(i, k)) * t;
  }
}
