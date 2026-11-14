// u0074 – ceres::Jet::operator*=
// Trích từ include/ceres/jet.h, dòng 275–278 (chỉ để xem, không compile)

  Jet<T, N>& operator*=(const T& s) {
    *this = *this * s;
    return *this;
  }
