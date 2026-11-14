// u1326 – ceres::internal::DynamicCompressedRowJacobianFinalizer::operator()
// Trích từ internal/ceres/dynamic_compressed_row_finalizer.h, dòng 41–45 (chỉ để xem, không compile)

  void operator()(SparseMatrix* base_jacobian, int num_parameters) {
    auto* jacobian =
        down_cast<DynamicCompressedRowSparseMatrix*>(base_jacobian);
    jacobian->Finalize(num_parameters);
  }
