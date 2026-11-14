// u0639 – ceres::Jet::operator/=
// Trích từ include/ceres/jet.h, dòng 259–262 (chỉ để xem, không compile)

  Jet<T, N>& operator/=(const Jet<T, N>& y) {
    *this = *this / y;
    return *this;
  }
