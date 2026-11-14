// u0127 – ceres::BesselJ1
// Trích từ include/ceres/jet.h, dòng 881–885 (chỉ để xem, không compile)

inline double BesselJ1(double x) {
  CERES_DISABLE_DEPRECATED_WARNING
  return j1(x);
  CERES_RESTORE_DEPRECATED_WARNING
}
