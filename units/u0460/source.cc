// u0460 – ceres::UnitQuaternionRotatePoint
// Trích từ include/ceres/rotation.h, dòng 721–741 (chỉ để xem, không compile)

template <typename T>
inline void UnitQuaternionRotatePoint(const T q[4],
                                      const T pt[3],
                                      T result[3]) {
  DCHECK_NE(pt, result) << "Inplace rotation is not supported.";

  // clang-format off
  T uv0 = q[2] * pt[2] - q[3] * pt[1];
  T uv1 = q[3] * pt[0] - q[1] * pt[2];
  T uv2 = q[1] * pt[1] - q[2] * pt[0];
  uv0 += uv0;
  uv1 += uv1;
  uv2 += uv2;
  result[0] = pt[0] + q[0] * uv0;
  result[1] = pt[1] + q[0] * uv1;
  result[2] = pt[2] + q[0] * uv2;
  result[0] += q[2] * uv2 - q[3] * uv1;
  result[1] += q[3] * uv0 - q[1] * uv2;
  result[2] += q[1] * uv1 - q[2] * uv0;
  // clang-format on
}
