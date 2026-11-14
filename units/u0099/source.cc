// u0099 – ceres::IsNormal
// Trích từ include/ceres/jet.h, dòng 516–517 (chỉ để xem, không compile)

CERES_DEPRECATED_WITH_MSG("ceres::IsNormal will be removed in a future Ceres Solver release. Please use ceres::isnormal.")
inline bool IsNormal(double x)   { return std::isnormal(x); }
