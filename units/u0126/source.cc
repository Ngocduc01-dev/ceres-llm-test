// u0126 – ceres::BesselJ0
// Trích từ include/ceres/jet.h, dòng 876–880 (chỉ để xem, không compile)

inline double BesselJ0(double x) {
  CERES_DISABLE_DEPRECATED_WARNING
  return j0(x);
  CERES_RESTORE_DEPRECATED_WARNING
}
