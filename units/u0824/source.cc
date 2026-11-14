// u0824 – ceres::internal::BlockJacobianWriter::Write
// Trích từ internal/ceres/block_jacobian_writer.h, dòng 78–85 (chỉ để xem, không compile)

  void Write(int /* residual_id */,
             int /* residual_offset */,
             double** /* jacobians */,
             SparseMatrix* /* jacobian */) {
    // This is a noop since the blocks were written directly into their final
    // position by the outside evaluate call, thanks to the jacobians array
    // prepared by the BlockEvaluatePreparers.
  }
