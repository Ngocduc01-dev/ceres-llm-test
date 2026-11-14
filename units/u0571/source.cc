// u0571 – ceres::TinySolver::Initialize
// Trích từ include/ceres/tiny_solver.h, dòng 382–393 (chỉ để xem, không compile)

  void Initialize(int num_residuals, int num_parameters) {
    dx_.resize(num_parameters);
    x_new_.resize(num_parameters);
    g_.resize(num_parameters);
    jacobi_scaling_.resize(num_parameters);
    lm_step_.resize(num_parameters);
    residuals_.resize(num_residuals);
    f_x_new_.resize(num_residuals);
    jacobian_.resize(num_residuals, num_parameters);
    jtj_.resize(num_parameters, num_parameters);
    jtj_regularized_.resize(num_parameters, num_parameters);
  }
