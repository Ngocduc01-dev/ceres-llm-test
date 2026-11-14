// u0782 – ceres::RotationMatrixToEulerAngles
// Trích từ include/ceres/rotation.h, dòng 562–629 (chỉ để xem, không compile)

template <typename EulerSystem, typename T, int row_stride, int col_stride>
void RotationMatrixToEulerAngles(
    const MatrixAdapter<const T, row_stride, col_stride>& R, T* euler) {
  using std::atan2;
  using std::fpclassify;
  using std::hypot;

  const auto [i, j, k] = EulerSystem::kAxes;

  T ea[3];
  if constexpr (EulerSystem::kIsProperEuler) {
    const T sy = hypot(R(i, j), R(i, k));
    if (fpclassify(sy) != FP_ZERO) {
      ea[0] = atan2(R(i, j), R(i, k));
      ea[1] = atan2(sy, R(i, i));
      ea[2] = atan2(R(j, i), -R(k, i));
    } else {
      ea[0] = atan2(-R(j, k), R(j, j));
      ea[1] = atan2(sy, R(i, i));
      ea[2] = T(0.0);
    }
  } else {
    const T cy = hypot(R(i, i), R(j, i));
    if (fpclassify(cy) != FP_ZERO) {
      ea[0] = atan2(R(k, j), R(k, k));
      ea[1] = atan2(-R(k, i), cy);
      ea[2] = atan2(R(j, i), R(i, i));
    } else {
      ea[0] = atan2(-R(j, k), R(j, j));
      ea[1] = atan2(-R(k, i), cy);
      ea[2] = T(0.0);
    }
  }
  if constexpr (EulerSystem::kIsParityOdd) {
    ea[0] = -ea[0];
    ea[1] = -ea[1];
    ea[2] = -ea[2];
  }
  euler[1] = ea[1];
  if constexpr (EulerSystem::kIsIntrinsic) {
    euler[0] = ea[2];
    euler[2] = ea[0];
  } else {
    euler[0] = ea[0];
    euler[2] = ea[2];
  }

  // Proper euler angles are defined for angles in
  //   [-pi, pi) x [0, pi / 2) x [-pi, pi)
  // which is enforced here
  if constexpr (EulerSystem::kIsProperEuler) {
    const T kPi(constants::pi);
    const T kTwoPi(2.0 * kPi);
    if (euler[1] < T(0.0) || ea[1] > kPi) {
      euler[0] += kPi;
      euler[1] = -euler[1];
      euler[2] -= kPi;
    }

    for (int i = 0; i < 3; ++i) {
      if (euler[i] < -kPi) {
        euler[i] += kTwoPi;
      } else if (euler[i] > kPi) {
        euler[i] -= kTwoPi;
      }
    }
  }
}
