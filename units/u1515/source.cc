// u1515 – ceres::internal::VisibilityBasedPreconditioner::VisibilityBasedPreconditioner
// Trích từ internal/ceres/visibility_based_preconditioner.cc, dòng 67–110 (chỉ để xem, không compile)

VisibilityBasedPreconditioner::VisibilityBasedPreconditioner(
    const CompressedRowBlockStructure& bs, Preconditioner::Options options)
    : options_(std::move(options)), num_blocks_(0), num_clusters_(0) {
  CHECK_GT(options_.elimination_groups.size(), 1);
  CHECK_GT(options_.elimination_groups[0], 0);
  CHECK(options_.type == CLUSTER_JACOBI || options_.type == CLUSTER_TRIDIAGONAL)
      << "Unknown preconditioner type: " << options_.type;
  num_blocks_ = bs.cols.size() - options_.elimination_groups[0];
  CHECK_GT(num_blocks_, 0) << "Jacobian should have at least 1 f_block for "
                           << "visibility based preconditioning.";
  CHECK(options_.context != nullptr);

  // Vector of camera block sizes
  blocks_ = Tail(bs.cols, bs.cols.size() - options_.elimination_groups[0]);

  const time_t start_time = time(nullptr);
  switch (options_.type) {
    case CLUSTER_JACOBI:
      ComputeClusterJacobiSparsity(bs);
      break;
    case CLUSTER_TRIDIAGONAL:
      ComputeClusterTridiagonalSparsity(bs);
      break;
    default:
      LOG(FATAL) << "Unknown preconditioner type";
  }
  const time_t structure_time = time(nullptr);
  InitStorage(bs);
  const time_t storage_time = time(nullptr);
  InitEliminator(bs);
  const time_t eliminator_time = time(nullptr);

  LinearSolver::Options sparse_cholesky_options;
  sparse_cholesky_options.sparse_linear_algebra_library_type =
      options_.sparse_linear_algebra_library_type;
  sparse_cholesky_options.ordering_type = options_.ordering_type;
  sparse_cholesky_ = SparseCholesky::Create(sparse_cholesky_options);

  const time_t init_time = time(nullptr);
  VLOG(2) << "init time: " << init_time - start_time
          << " structure time: " << structure_time - start_time
          << " storage time:" << storage_time - structure_time
          << " eliminator time: " << eliminator_time - storage_time;
}
