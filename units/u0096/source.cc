// u0096 – ceres::IsFinite
// Trích từ include/ceres/jet.h, dòng 510–511 (chỉ để xem, không compile)

CERES_DEPRECATED_WITH_MSG("ceres::IsFinite will be removed in a future Ceres Solver release. Please use ceres::isfinite.")
inline bool IsFinite(double x)   { return std::isfinite(x); }
