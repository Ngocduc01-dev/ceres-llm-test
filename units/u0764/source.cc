// u0764 – ceres::internal::operator<<
// Trích từ internal/ceres/linear_solver.h, dòng 76–95 (chỉ để xem, không compile)

inline std::ostream& operator<<(std::ostream& s,
                                LinearSolverTerminationType type) {
  switch (type) {
    case LinearSolverTerminationType::SUCCESS:
      s << "LINEAR_SOLVER_SUCCESS";
      break;
    case LinearSolverTerminationType::NO_CONVERGENCE:
      s << "LINEAR_SOLVER_NO_CONVERGENCE";
      break;
    case LinearSolverTerminationType::FAILURE:
      s << "LINEAR_SOLVER_FAILURE";
      break;
    case LinearSolverTerminationType::FATAL_ERROR:
      s << "LINEAR_SOLVER_FATAL_ERROR";
      break;
    default:
      s << "UNKNOWN LinearSolverTerminationType";
  }
  return s;
}
