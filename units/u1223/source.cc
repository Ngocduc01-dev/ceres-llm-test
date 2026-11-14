// u1223 – ceres::internal::VisibilityBasedPreconditioner::InitEliminator
// Trích từ internal/ceres/visibility_based_preconditioner.cc, dòng 302–315 (chỉ để xem, không compile)

void VisibilityBasedPreconditioner::InitEliminator(
    const CompressedRowBlockStructure& bs) {
  LinearSolver::Options eliminator_options;
  eliminator_options.elimination_groups = options_.elimination_groups;
  eliminator_options.num_threads = options_.num_threads;
  eliminator_options.e_block_size = options_.e_block_size;
  eliminator_options.f_block_size = options_.f_block_size;
  eliminator_options.row_block_size = options_.row_block_size;
  eliminator_options.context = options_.context;
  eliminator_ = SchurEliminatorBase::Create(eliminator_options);
  const bool kFullRankETE = true;
  eliminator_->Init(
      eliminator_options.elimination_groups[0], kFullRankETE, &bs);
}
