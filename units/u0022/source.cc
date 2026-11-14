// u0022 – ceres::GradientProblem::mutable_function
// Trích từ include/ceres/gradient_problem.h, dòng 110–110 (chỉ để xem, không compile)

  FirstOrderFunction* mutable_function() { return function_.get(); }
