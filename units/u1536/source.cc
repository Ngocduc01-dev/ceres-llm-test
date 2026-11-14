// u1536 – ceres::Solve
// Trích từ internal/ceres/solver.cc, dòng 832–837 (chỉ để xem, không compile)

void Solve(const Solver::Options& options,
           Problem* problem,
           Solver::Summary* summary) {
  Solver solver;
  solver.Solve(options, problem, summary);
}
