// u0336 – ceres::ComposedLoss::Evaluate
// Trích từ internal/ceres/loss_function.cc, dòng 154–163 (chỉ để xem, không compile)

void ComposedLoss::Evaluate(double s, double rho[3]) const {
  double rho_f[3], rho_g[3];
  g_->Evaluate(s, rho_g);
  f_->Evaluate(rho_g[0], rho_f);
  rho[0] = rho_f[0];
  // f'(g(s)) * g'(s).
  rho[1] = rho_f[1] * rho_g[1];
  // f''(g(s)) * g'(s) * g'(s) + f'(g(s)) * g''(s).
  rho[2] = rho_f[2] * rho_g[1] * rho_g[1] + rho_f[1] * rho_g[2];
}
