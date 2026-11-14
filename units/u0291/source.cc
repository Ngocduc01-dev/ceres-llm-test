// u0291 – ceres::internal::EigenSparse::IsNestedDissectionAvailable
// Trích từ internal/ceres/eigensparse.h, dòng 53–59 (chỉ để xem, không compile)

  static constexpr bool IsNestedDissectionAvailable() noexcept {
#ifdef CERES_NO_EIGEN_METIS
    return false;
#else
    return true;
#endif
  }
