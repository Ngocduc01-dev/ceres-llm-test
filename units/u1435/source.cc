// u1435 – ceres::internal::BlockJacobianWriter::BlockJacobianWriter
// Trích từ internal/ceres/block_jacobian_writer.cc, dòng 169–179 (chỉ để xem, không compile)

BlockJacobianWriter::BlockJacobianWriter(const Evaluator::Options& options,
                                         Program* program)
    : options_(options), program_(program) {
  CHECK_GE(options.num_eliminate_blocks, 0)
      << "num_eliminate_blocks must be greater than 0.";

  jacobian_layout_is_valid_ = BuildJacobianLayout(*program,
                                                  options.num_eliminate_blocks,
                                                  &jacobian_layout_,
                                                  &jacobian_layout_storage_);
}
