// u0973 – ceres::internal::TrustRegionMinimizer::Init
// Trích từ internal/ceres/trust_region_minimizer.cc, dòng 139–188 (chỉ để xem, không compile)

void TrustRegionMinimizer::Init(const Minimizer::Options& options,
                                double* parameters,
                                Solver::Summary* solver_summary) {
  options_ = options;
  std::sort(options_.trust_region_minimizer_iterations_to_dump.begin(),
            options_.trust_region_minimizer_iterations_to_dump.end());

  parameters_ = parameters;

  solver_summary_ = solver_summary;
  solver_summary_->termination_type = NO_CONVERGENCE;
  solver_summary_->num_successful_steps = 0;
  solver_summary_->num_unsuccessful_steps = 0;
  solver_summary_->is_constrained = options.is_constrained;

  CHECK(options_.evaluator != nullptr);
  CHECK(options_.jacobian != nullptr);
  CHECK(options_.trust_region_strategy != nullptr);
  evaluator_ = options_.evaluator.get();
  jacobian_ = options_.jacobian.get();
  strategy_ = options_.trust_region_strategy.get();

  is_not_silent_ = !options.is_silent;
  inner_iterations_are_enabled_ =
      options.inner_iteration_minimizer.get() != nullptr;
  inner_iterations_were_useful_ = false;

  num_parameters_ = evaluator_->NumParameters();
  num_effective_parameters_ = evaluator_->NumEffectiveParameters();
  num_residuals_ = evaluator_->NumResiduals();
  num_consecutive_invalid_steps_ = 0;

  x_ = ConstVectorRef(parameters_, num_parameters_);
  residuals_.resize(num_residuals_);
  trust_region_step_.resize(num_effective_parameters_);
  delta_.resize(num_effective_parameters_);
  candidate_x_.resize(num_parameters_);
  gradient_.resize(num_effective_parameters_);
  model_residuals_.resize(num_residuals_);
  negative_gradient_.resize(num_effective_parameters_);
  projected_gradient_step_.resize(num_parameters_);

  // By default scaling is one, if the user requests Jacobi scaling of
  // the Jacobian, we will compute and overwrite this vector.
  jacobian_scaling_ = Vector::Ones(num_effective_parameters_);

  x_cost_ = std::numeric_limits<double>::max();
  minimum_cost_ = x_cost_;
  model_cost_change_ = 0.0;
}
