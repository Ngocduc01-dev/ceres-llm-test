// u0923 – ceres::internal::SchurEliminatorBase::Create
// Trích từ internal/ceres/schur_eliminator.cc, dòng 51–161 (chỉ để xem, không compile)

std::unique_ptr<SchurEliminatorBase> SchurEliminatorBase::Create(
    const LinearSolver::Options& options) {
#ifndef CERES_RESTRICT_SCHUR_SPECIALIZATION
  if ((options.row_block_size == 2) &&
     (options.e_block_size == 2) &&
     (options.f_block_size == 2)) {
    return std::make_unique<SchurEliminator<2, 2, 2>>(options);
  }
  if ((options.row_block_size == 2) &&
     (options.e_block_size == 2) &&
     (options.f_block_size == 3)) {
    return std::make_unique<SchurEliminator<2, 2, 3>>(options);
  }
  if ((options.row_block_size == 2) &&
     (options.e_block_size == 2) &&
     (options.f_block_size == 4)) {
    return std::make_unique<SchurEliminator<2, 2, 4>>(options);
  }
  if ((options.row_block_size == 2) &&
     (options.e_block_size == 2)) {
    return std::make_unique<SchurEliminator<2, 2, Eigen::Dynamic>>(options);
  }
  if ((options.row_block_size == 2) &&
     (options.e_block_size == 3) &&
     (options.f_block_size == 3)) {
    return std::make_unique<SchurEliminator<2, 3, 3>>(options);
  }
  if ((options.row_block_size == 2) &&
     (options.e_block_size == 3) &&
     (options.f_block_size == 4)) {
    return std::make_unique<SchurEliminator<2, 3, 4>>(options);
  }
  if ((options.row_block_size == 2) &&
     (options.e_block_size == 3) &&
     (options.f_block_size == 6)) {
    return std::make_unique<SchurEliminator<2, 3, 6>>(options);
  }
  if ((options.row_block_size == 2) &&
     (options.e_block_size == 3) &&
     (options.f_block_size == 9)) {
    return std::make_unique<SchurEliminator<2, 3, 9>>(options);
  }
  if ((options.row_block_size == 2) &&
     (options.e_block_size == 3)) {
    return std::make_unique<SchurEliminator<2, 3, Eigen::Dynamic>>(options);
  }
  if ((options.row_block_size == 2) &&
     (options.e_block_size == 4) &&
     (options.f_block_size == 3)) {
    return std::make_unique<SchurEliminator<2, 4, 3>>(options);
  }
  if ((options.row_block_size == 2) &&
     (options.e_block_size == 4) &&
     (options.f_block_size == 4)) {
    return std::make_unique<SchurEliminator<2, 4, 4>>(options);
  }
  if ((options.row_block_size == 2) &&
     (options.e_block_size == 4) &&
     (options.f_block_size == 6)) {
    return std::make_unique<SchurEliminator<2, 4, 6>>(options);
  }
  if ((options.row_block_size == 2) &&
     (options.e_block_size == 4) &&
     (options.f_block_size == 8)) {
    return std::make_unique<SchurEliminator<2, 4, 8>>(options);
  }
  if ((options.row_block_size == 2) &&
     (options.e_block_size == 4) &&
     (options.f_block_size == 9)) {
    return std::make_unique<SchurEliminator<2, 4, 9>>(options);
  }
  if ((options.row_block_size == 2) &&
     (options.e_block_size == 4)) {
    return std::make_unique<SchurEliminator<2, 4, Eigen::Dynamic>>(options);
  }
  if (options.row_block_size == 2) {
    return std::make_unique<SchurEliminator<2, Eigen::Dynamic, Eigen::Dynamic>>(options);
  }
  if ((options.row_block_size == 3) &&
     (options.e_block_size == 3) &&
     (options.f_block_size == 3)) {
    return std::make_unique<SchurEliminator<3, 3, 3>>(options);
  }
  if ((options.row_block_size == 4) &&
     (options.e_block_size == 4) &&
     (options.f_block_size == 2)) {
    return std::make_unique<SchurEliminator<4, 4, 2>>(options);
  }
  if ((options.row_block_size == 4) &&
     (options.e_block_size == 4) &&
     (options.f_block_size == 3)) {
    return std::make_unique<SchurEliminator<4, 4, 3>>(options);
  }
  if ((options.row_block_size == 4) &&
     (options.e_block_size == 4) &&
     (options.f_block_size == 4)) {
    return std::make_unique<SchurEliminator<4, 4, 4>>(options);
  }
  if ((options.row_block_size == 4) &&
     (options.e_block_size == 4)) {
    return std::make_unique<SchurEliminator<4, 4, Eigen::Dynamic>>(options);
  }

#endif
  VLOG(1) << "Template specializations not found for <"
          << options.row_block_size << "," << options.e_block_size << ","
          << options.f_block_size << ">";
  return std::make_unique<SchurEliminator<Eigen::Dynamic,
                                          Eigen::Dynamic,
                                          Eigen::Dynamic>>(options);
}
