// u1539 – ceres_solve
// Trích từ internal/ceres/c_api.cc, dòng 171–185 (chỉ để xem, không compile)

void ceres_solve(ceres_problem_t* c_problem) {
  auto* problem = reinterpret_cast<Problem*>(c_problem);

  // TODO(keir): Obviously, this way of setting options won't scale or last.
  // Instead, figure out a way to specify some of the options without
  // duplicating everything.
  ceres::Solver::Options options;
  options.max_num_iterations = 100;
  options.linear_solver_type = ceres::DENSE_QR;
  options.minimizer_progress_to_stdout = true;

  ceres::Solver::Summary summary;
  ceres::Solve(options, problem, &summary);
  std::cout << summary.FullReport() << "\n";
}
