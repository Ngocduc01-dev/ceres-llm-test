// u0801 – ceres::(anonymous)::IsIterativeSolver
// Trích từ internal/ceres/solver.cc, dòng 119–121 (chỉ để xem, không compile)

bool IsIterativeSolver(LinearSolverType type) {
  return (type == CGNR || type == ITERATIVE_SCHUR);
}
