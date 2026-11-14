// u0459 – ceres::AngleAxisToQuaternion
// Trích từ include/ceres/rotation.h, dòng 314–342 (chỉ để xem, không compile)

template <typename T>
inline void AngleAxisToQuaternion(const T* angle_axis, T* quaternion) {
  using std::fpclassify;
  using std::hypot;
  const T& a0 = angle_axis[0];
  const T& a1 = angle_axis[1];
  const T& a2 = angle_axis[2];
  const T theta = hypot(a0, a1, a2);

  // For points not at the origin, the full conversion is numerically stable.
  if (fpclassify(theta) != FP_ZERO) {
    const T half_theta = theta * T(0.5);
    const T k = sin(half_theta) / theta;
    quaternion[0] = cos(half_theta);
    quaternion[1] = a0 * k;
    quaternion[2] = a1 * k;
    quaternion[3] = a2 * k;
  } else {
    // At the origin, sqrt() will produce NaN in the derivative since
    // the argument is zero.  By approximating with a Taylor series,
    // and truncating at one term, the value and first derivatives will be
    // computed correctly when Jets are used.
    const T k(0.5);
    quaternion[0] = T(1.0);
    quaternion[1] = a0 * k;
    quaternion[2] = a1 * k;
    quaternion[3] = a2 * k;
  }
}
