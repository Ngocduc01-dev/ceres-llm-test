// u0968 – ceres::internal::BlockSparseMatrix::FreeValues
// Trích từ internal/ceres/block_sparse_matrix.cc, dòng 827–841 (chỉ để xem, không compile)

void BlockSparseMatrix::FreeValues(double*& values) {
  if (!use_page_locked_memory_) {
    delete[] values;
    values = nullptr;
    return;
  }

#ifndef CERES_NO_CUDA
  CHECK_EQ(cudaSuccess, cudaFreeHost(values));
  values = nullptr;
#else
  LOG(FATAL) << "Page locked memory requested when CUDA is not available. "
             << "This is a Ceres bug; please contact the developers!";
#endif
};
