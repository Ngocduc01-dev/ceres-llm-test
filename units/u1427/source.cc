// u1427 – ceres::Problem::Problem
// Trích từ internal/ceres/problem.cc, dòng 43–44 (chỉ để xem, không compile)

Problem::Problem(const Problem::Options& options)
    : impl_(new internal::ProblemImpl(options)) {}
