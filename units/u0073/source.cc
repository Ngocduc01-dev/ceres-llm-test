// u0073 – ceres::Jet::operator-=
// Trích từ include/ceres/jet.h, dòng 270–273 (chỉ để xem, không compile)

  Jet<T, N>& operator-=(const T& s) {
    *this = *this - s;
    return *this;
  }
