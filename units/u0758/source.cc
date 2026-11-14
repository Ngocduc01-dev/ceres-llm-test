// u0758 – ceres::IsDenseLinearAlgebraLibraryTypeAvailable
// Trích từ internal/ceres/types.cc, dòng 440–464 (chỉ để xem, không compile)

bool IsDenseLinearAlgebraLibraryTypeAvailable(
    DenseLinearAlgebraLibraryType type) {
  if (type == EIGEN) {
    return true;
  }

  if (type == LAPACK) {
#ifdef CERES_NO_LAPACK
    return false;
#else
    return true;
#endif
  }

  if (type == CUDA) {
#ifdef CERES_NO_CUDA
    return false;
#else
    return true;
#endif
  }

  LOG(WARNING) << "Unknown dense linear algebra library " << type;
  return false;
}
