// u1133 – ceres::internal::VisibilityBasedPreconditioner::InitStorage
// Trích từ internal/ceres/visibility_based_preconditioner.cc, dòng 157–162 (chỉ để xem, không compile)

void VisibilityBasedPreconditioner::InitStorage(
    const CompressedRowBlockStructure& bs) {
  ComputeBlockPairsInPreconditioner(bs);
  m_ = std::make_unique<BlockRandomAccessSparseMatrix>(
      blocks_, block_pairs_, options_.context, options_.num_threads);
}
