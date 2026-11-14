// u1355 – ceres::internal::GradientProblemEvaluator::Evaluate
// Trích từ internal/ceres/gradient_problem_evaluator.h, dòng 55–74 (chỉ để xem, không compile)

  bool Evaluate(const EvaluateOptions& /*evaluate_options*/,
                const double* state,
                double* cost,
                double* /*residuals*/,
                double* gradient,
                SparseMatrix* jacobian) final {
    CHECK(jacobian == nullptr);
    ScopedExecutionTimer total_timer("Evaluator::Total", &execution_summary_);
    // The reason we use Residual and Jacobian here even when we are
    // only computing the cost and gradient has to do with the fact
    // that the line search minimizer code is used by both the
    // GradientProblemSolver and the main CeresSolver coder where the
    // Evaluator evaluates the Jacobian, and these magic strings need
    // to be consistent across the code base for the time accounting
    // to work.
    ScopedExecutionTimer call_type_timer(
        gradient == nullptr ? "Evaluator::Residual" : "Evaluator::Jacobian",
        &execution_summary_);
    return problem_.Evaluate(state, cost, gradient);
  }
