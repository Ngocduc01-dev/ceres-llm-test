// u1514 – ceres::internal::ProgramEvaluator::ProgramEvaluator<EvaluatePreparer, JacobianWriter, JacobianFinalizer>
// Trích từ internal/ceres/program_evaluator.h, dòng 117–127 (chỉ để xem, không compile)

  ProgramEvaluator(const Evaluator::Options& options, Program* program)
      : options_(options),
        program_(program),
        jacobian_writer_(options, program),
        evaluate_preparers_(std::move(
            jacobian_writer_.CreateEvaluatePreparers(options.num_threads))),
        num_parameters_(program->NumEffectiveParameters()) {
    BuildResidualLayout(*program, &residual_layout_);
    evaluate_scratch_ = std::move(CreateEvaluatorScratch(
        *program, static_cast<unsigned>(options.num_threads)));
  }
