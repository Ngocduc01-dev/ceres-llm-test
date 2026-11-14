// u0097 – ceres::IsInfinite
// Trích từ include/ceres/jet.h, dòng 512–513 (chỉ để xem, không compile)

CERES_DEPRECATED_WITH_MSG("ceres::IsInfinite will be removed in a future Ceres Solver release. Please use ceres::isinf.")
inline bool IsInfinite(double x) { return std::isinf(x);    }
