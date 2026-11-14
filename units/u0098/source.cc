// u0098 – ceres::IsNaN
// Trích từ include/ceres/jet.h, dòng 514–515 (chỉ để xem, không compile)

CERES_DEPRECATED_WITH_MSG("ceres::IsNaN will be removed in a future Ceres Solver release. Please use ceres::isnan.")
inline bool IsNaN(double x)      { return std::isnan(x);    }
