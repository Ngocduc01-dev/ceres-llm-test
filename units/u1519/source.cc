// u1519 – ceres::Solver::Options::IsValid
// Trích từ internal/ceres/solver.cc, dòng 690–706 (chỉ để xem, không compile)

bool Solver::Options::IsValid(std::string* error) const {
  if (!CommonOptionsAreValid(*this, error)) {
    return false;
  }

  if (minimizer_type == TRUST_REGION &&
      !TrustRegionOptionsAreValid(*this, error)) {
    return false;
  }

  // We do not know if the problem is bounds constrained or not, if it
  // is then the trust region solver will also use the line search
  // solver to do a projection onto the box constraints, so make sure
  // that the line search options are checked independent of what
  // minimizer algorithm is being used.
  return LineSearchOptionsAreValid(*this, error);
}
