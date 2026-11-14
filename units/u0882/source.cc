// u0882 – ceres::Problem::mutable_impl
// Trích từ internal/ceres/problem.cc, dòng 215–215 (chỉ để xem, không compile)

internal::ProblemImpl* Problem::mutable_impl() { return impl_.get(); }
