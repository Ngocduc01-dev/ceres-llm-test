// u0745 – ceres::EulerAnglesToRotation
// Trích từ include/ceres/rotation.h, dòng 501–555 (chỉ để xem, không compile)

template <typename EulerSystem, typename T, int row_stride, int col_stride>
void EulerAnglesToRotation(const T* euler,
                           const MatrixAdapter<T, row_stride, col_stride>& R) {
  using std::cos;
  using std::sin;

  const auto [i, j, k] = EulerSystem::kAxes;

  T ea[3];
  ea[1] = euler[1];
  if constexpr (EulerSystem::kIsIntrinsic) {
    ea[0] = euler[2];
    ea[2] = euler[0];
  } else {
    ea[0] = euler[0];
    ea[2] = euler[2];
  }
  if constexpr (EulerSystem::kIsParityOdd) {
    ea[0] = -ea[0];
    ea[1] = -ea[1];
    ea[2] = -ea[2];
  }

  const T ci = cos(ea[0]);
  const T cj = cos(ea[1]);
  const T ch = cos(ea[2]);
  const T si = sin(ea[0]);
  const T sj = sin(ea[1]);
  const T sh = sin(ea[2]);
  const T cc = ci * ch;
  const T cs = ci * sh;
  const T sc = si * ch;
  const T ss = si * sh;
  if constexpr (EulerSystem::kIsProperEuler) {
    R(i, i) = cj;
    R(i, j) = sj * si;
    R(i, k) = sj * ci;
    R(j, i) = sj * sh;
    R(j, j) = -cj * ss + cc;
    R(j, k) = -cj * cs - sc;
    R(k, i) = -sj * ch;
    R(k, j) = cj * sc + cs;
    R(k, k) = cj * cc - ss;
  } else {
    R(i, i) = cj * ch;
    R(i, j) = sj * sc - cs;
    R(i, k) = sj * cc + ss;
    R(j, i) = cj * sh;
    R(j, j) = sj * ss + cc;
    R(j, k) = sj * cs - sc;
    R(k, i) = -sj;
    R(k, j) = cj * si;
    R(k, k) = cj * ci;
  }
}
