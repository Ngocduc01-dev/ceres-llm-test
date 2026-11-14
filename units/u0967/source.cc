// u0967 – ceres::internal::BlockSparseMatrix::AllocateValues
// Trích từ internal/ceres/block_sparse_matrix.cc, dòng 809–825 (chỉ để xem, không compile)

double* BlockSparseMatrix::AllocateValues(int size) {
  if (!use_page_locked_memory_) {
    return new double[size];
  }

#ifndef CERES_NO_CUDA

  double* values = nullptr;
  CHECK_EQ(cudaSuccess,
           cudaHostAlloc(&values, sizeof(double) * size, cudaHostAllocDefault));
  return values;
#else
  LOG(FATAL) << "Page locked memory requested when CUDA is not available. "
             << "This is a Ceres bug; please contact the developers!";
  return nullptr;
#endif
};
