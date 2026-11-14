// u0498 – ceres::QuaternionToAngleAxis
// Trích từ include/ceres/rotation.h, dòng 344–388 (chỉ để xem, không compile)

template <typename T>
inline void QuaternionToAngleAxis(const T* quaternion, T* angle_axis) {
  using std::fpclassify;
  using std::hypot;
  const T& q1 = quaternion[1];
  const T& q2 = quaternion[2];
  const T& q3 = quaternion[3];
  const T sin_theta = hypot(q1, q2, q3);

  // For quaternions representing non-zero rotation, the conversion
  // is numerically stable.
  if (fpclassify(sin_theta) != FP_ZERO) {
    const T& cos_theta = quaternion[0];

    // If cos_theta is negative, theta is greater than pi/2, which
    // means that angle for the angle_axis vector which is 2 * theta
    // would be greater than pi.
    //
    // While this will result in the correct rotation, it does not
    // result in a normalized angle-axis vector.
    //
    // In that case we observe that 2 * theta ~ 2 * theta - 2 * pi,
    // which is equivalent saying
    //
    //   theta - pi = atan(sin(theta - pi), cos(theta - pi))
    //              = atan(-sin(theta), -cos(theta))
    //
    const T two_theta =
        T(2.0) * ((cos_theta < T(0.0)) ? atan2(-sin_theta, -cos_theta)
                                       : atan2(sin_theta, cos_theta));
    const T k = two_theta / sin_theta;
    angle_axis[0] = q1 * k;
    angle_axis[1] = q2 * k;
    angle_axis[2] = q3 * k;
  } else {
    // For zero rotation, sqrt() will produce NaN in the derivative since
    // the argument is zero.  By approximating with a Taylor series,
    // and truncating at one term, the value and first derivatives will be
    // computed correctly when Jets are used.
    const T k(2.0);
    angle_axis[0] = q1 * k;
    angle_axis[1] = q2 * k;
    angle_axis[2] = q3 * k;
  }
}
