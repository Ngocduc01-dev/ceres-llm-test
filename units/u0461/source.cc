// u0461 – ceres::QuaternionRotatePoint
// Trích từ include/ceres/rotation.h, dòng 743–760 (chỉ để xem, không compile)

template <typename T>
inline void QuaternionRotatePoint(const T q[4], const T pt[3], T result[3]) {
  DCHECK_NE(pt, result) << "Inplace rotation is not supported.";

  // 'scale' is 1 / norm(q).
  const T scale =
      T(1) / sqrt(q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);

  // Make unit-norm version of q.
  const T unit[4] = {
      scale * q[0],
      scale * q[1],
      scale * q[2],
      scale * q[3],
  };

  UnitQuaternionRotatePoint(unit, pt, result);
}
