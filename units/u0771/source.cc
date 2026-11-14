// u0771 – ceres::IsSparseLinearAlgebraLibraryTypeAvailable
// Trích từ internal/ceres/types.cc, dòng 398–438 (chỉ để xem, không compile)

bool IsSparseLinearAlgebraLibraryTypeAvailable(
    SparseLinearAlgebraLibraryType type) {
  if (type == SUITE_SPARSE) {
#ifdef CERES_NO_SUITESPARSE
    return false;
#else
    return true;
#endif
  }

  if (type == ACCELERATE_SPARSE) {
#ifdef CERES_NO_ACCELERATE_SPARSE
    return false;
#else
    return true;
#endif
  }

  if (type == EIGEN_SPARSE) {
#ifdef CERES_USE_EIGEN_SPARSE
    return true;
#else
    return false;
#endif
  }

  if (type == CUDA_SPARSE) {
#ifdef CERES_NO_CUDA
    return false;
#else
    return true;
#endif
  }

  if (type == NO_SPARSE) {
    return true;
  }

  LOG(WARNING) << "Unknown sparse linear algebra library " << type;
  return false;
}
