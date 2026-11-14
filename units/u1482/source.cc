// u1482 – ceres_create_problem
// Trích từ internal/ceres/c_api.cc, dòng 58–60 (chỉ để xem, không compile)

ceres_problem_t* ceres_create_problem() {
  return reinterpret_cast<ceres_problem_t*>(new Problem);
}
