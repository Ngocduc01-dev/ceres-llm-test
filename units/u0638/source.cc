// u0638 – ceres::Jet::operator*=
// Trích từ include/ceres/jet.h, dòng 254–257 (chỉ để xem, không compile)

  Jet<T, N>& operator*=(const Jet<T, N>& y) {
    *this = *this * y;
    return *this;
  }
