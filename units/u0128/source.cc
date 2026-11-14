// u0128 – ceres::BesselJn
// Trích từ include/ceres/jet.h, dòng 886–890 (chỉ để xem, không compile)

inline double BesselJn(int n, double x) {
  CERES_DISABLE_DEPRECATED_WARNING
  return jn(n, x);
  CERES_RESTORE_DEPRECATED_WARNING
}
