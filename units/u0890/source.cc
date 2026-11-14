// u0890 – ceres::internal::GetBestSchurTemplateSpecialization
// Trích từ internal/ceres/schur_templates.cc, dòng 48–224 (chỉ để xem, không compile)

void GetBestSchurTemplateSpecialization(int* row_block_size,
                                        int* e_block_size,
                                        int* f_block_size) {
  LinearSolver::Options options;
  options.row_block_size = *row_block_size;
  options.e_block_size = *e_block_size;
  options.f_block_size = *f_block_size;
  *row_block_size = Eigen::Dynamic;
  *e_block_size = Eigen::Dynamic;
  *f_block_size = Eigen::Dynamic;
#ifndef CERES_RESTRICT_SCHUR_SPECIALIZATION
  if ((options.row_block_size == 2) &&
     (options.e_block_size == 2) &&
     (options.f_block_size == 2)) {
    *row_block_size = 2;
    *e_block_size = 2;
    *f_block_size = 2;
    return;
  }
  if ((options.row_block_size == 2) &&
     (options.e_block_size == 2) &&
     (options.f_block_size == 3)) {
    *row_block_size = 2;
    *e_block_size = 2;
    *f_block_size = 3;
    return;
  }
  if ((options.row_block_size == 2) &&
     (options.e_block_size == 2) &&
     (options.f_block_size == 4)) {
    *row_block_size = 2;
    *e_block_size = 2;
    *f_block_size = 4;
    return;
  }
  if ((options.row_block_size == 2) &&
     (options.e_block_size == 2)) {
    *row_block_size = 2;
    *e_block_size = 2;
    *f_block_size = Eigen::Dynamic;
    return;
  }
  if ((options.row_block_size == 2) &&
     (options.e_block_size == 3) &&
     (options.f_block_size == 3)) {
    *row_block_size = 2;
    *e_block_size = 3;
    *f_block_size = 3;
    return;
  }
  if ((options.row_block_size == 2) &&
     (options.e_block_size == 3) &&
     (options.f_block_size == 4)) {
    *row_block_size = 2;
    *e_block_size = 3;
    *f_block_size = 4;
    return;
  }
  if ((options.row_block_size == 2) &&
     (options.e_block_size == 3) &&
     (options.f_block_size == 6)) {
    *row_block_size = 2;
    *e_block_size = 3;
    *f_block_size = 6;
    return;
  }
  if ((options.row_block_size == 2) &&
     (options.e_block_size == 3) &&
     (options.f_block_size == 9)) {
    *row_block_size = 2;
    *e_block_size = 3;
    *f_block_size = 9;
    return;
  }
  if ((options.row_block_size == 2) &&
     (options.e_block_size == 3)) {
    *row_block_size = 2;
    *e_block_size = 3;
    *f_block_size = Eigen::Dynamic;
    return;
  }
  if ((options.row_block_size == 2) &&
     (options.e_block_size == 4) &&
     (options.f_block_size == 3)) {
    *row_block_size = 2;
    *e_block_size = 4;
    *f_block_size = 3;
    return;
  }
  if ((options.row_block_size == 2) &&
     (options.e_block_size == 4) &&
     (options.f_block_size == 4)) {
    *row_block_size = 2;
    *e_block_size = 4;
    *f_block_size = 4;
    return;
  }
  if ((options.row_block_size == 2) &&
     (options.e_block_size == 4) &&
     (options.f_block_size == 6)) {
    *row_block_size = 2;
    *e_block_size = 4;
    *f_block_size = 6;
    return;
  }
  if ((options.row_block_size == 2) &&
     (options.e_block_size == 4) &&
     (options.f_block_size == 8)) {
    *row_block_size = 2;
    *e_block_size = 4;
    *f_block_size = 8;
    return;
  }
  if ((options.row_block_size == 2) &&
     (options.e_block_size == 4) &&
     (options.f_block_size == 9)) {
    *row_block_size = 2;
    *e_block_size = 4;
    *f_block_size = 9;
    return;
  }
  if ((options.row_block_size == 2) &&
     (options.e_block_size == 4)) {
    *row_block_size = 2;
    *e_block_size = 4;
    *f_block_size = Eigen::Dynamic;
    return;
  }
  if (options.row_block_size == 2) {
    *row_block_size = 2;
    *e_block_size = Eigen::Dynamic;
    *f_block_size = Eigen::Dynamic;
    return;
  }
  if ((options.row_block_size == 3) &&
     (options.e_block_size == 3) &&
     (options.f_block_size == 3)) {
    *row_block_size = 3;
    *e_block_size = 3;
    *f_block_size = 3;
    return;
  }
  if ((options.row_block_size == 4) &&
     (options.e_block_size == 4) &&
     (options.f_block_size == 2)) {
    *row_block_size = 4;
    *e_block_size = 4;
    *f_block_size = 2;
    return;
  }
  if ((options.row_block_size == 4) &&
     (options.e_block_size == 4) &&
     (options.f_block_size == 3)) {
    *row_block_size = 4;
    *e_block_size = 4;
    *f_block_size = 3;
    return;
  }
  if ((options.row_block_size == 4) &&
     (options.e_block_size == 4) &&
     (options.f_block_size == 4)) {
    *row_block_size = 4;
    *e_block_size = 4;
    *f_block_size = 4;
    return;
  }
  if ((options.row_block_size == 4) &&
     (options.e_block_size == 4)) {
    *row_block_size = 4;
    *e_block_size = 4;
    *f_block_size = Eigen::Dynamic;
    return;
  }

#endif
  return;
}
