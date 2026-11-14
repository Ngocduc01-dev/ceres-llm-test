// u1492 – ceres::internal::ProgramEvaluator::Evaluate
// Trích từ internal/ceres/program_evaluator.h, dòng 134–301 (chỉ để xem, không compile)

  bool Evaluate(const Evaluator::EvaluateOptions& evaluate_options,
                const double* state,
                double* cost,
                double* residuals,
                double* gradient,
                SparseMatrix* jacobian) final {
    ScopedExecutionTimer total_timer("Evaluator::Total", &execution_summary_);
    ScopedExecutionTimer call_type_timer(
        gradient == nullptr && jacobian == nullptr ? "Evaluator::Residual"
                                                   : "Evaluator::Jacobian",
        &execution_summary_);

    // The parameters are stateful, so set the state before evaluating.
    if (!program_->StateVectorToParameterBlocks(state)) {
      return false;
    }

    // Notify the user about a new evaluation point if they are interested.
    if (options_.evaluation_callback != nullptr) {
      program_->CopyParameterBlockStateToUserState();
      options_.evaluation_callback->PrepareForEvaluation(
          /*jacobians=*/(gradient != nullptr || jacobian != nullptr),
          evaluate_options.new_evaluation_point);
    }

    if (residuals != nullptr) {
      ParallelSetZero(options_.context,
                      options_.num_threads,
                      residuals,
                      program_->NumResiduals());
    }

    if (jacobian != nullptr) {
      jacobian->SetZero(options_.context, options_.num_threads);
    }

    // Each thread gets it's own cost and evaluate scratch space.
    for (int i = 0; i < options_.num_threads; ++i) {
      evaluate_scratch_[i].cost = 0.0;
      if (gradient != nullptr) {
        ParallelSetZero(options_.context,
                        options_.num_threads,
                        evaluate_scratch_[i].gradient.get(),
                        num_parameters_);
      }
    }

    const int num_residual_blocks = program_->NumResidualBlocks();
    // This bool is used to disable the loop if an error is encountered without
    // breaking out of it. The remaining loop iterations are still run, but with
    // an empty body, and so will finish quickly.
    std::atomic_bool abort(false);
    ParallelFor(
        options_.context,
        0,
        num_residual_blocks,
        options_.num_threads,
        [&](int thread_id, int i) {
          if (abort) {
            return;
          }

          EvaluatePreparer* preparer = &evaluate_preparers_[thread_id];
          EvaluateScratch* scratch = &evaluate_scratch_[thread_id];

          // Prepare block residuals if requested.
          const ResidualBlock* residual_block = program_->residual_blocks()[i];
          double* block_residuals = nullptr;
          if (residuals != nullptr) {
            block_residuals = residuals + residual_layout_[i];
          } else if (gradient != nullptr) {
            block_residuals = scratch->residual_block_residuals.get();
          }

          // Prepare block jacobians if requested.
          double** block_jacobians = nullptr;
          if (jacobian != nullptr || gradient != nullptr) {
            preparer->Prepare(residual_block,
                              i,
                              jacobian,
                              scratch->jacobian_block_ptrs.get());
            block_jacobians = scratch->jacobian_block_ptrs.get();
          }

          // Evaluate the cost, residuals, and jacobians.
          double block_cost;
          if (!residual_block->Evaluate(
                  evaluate_options.apply_loss_function,
                  &block_cost,
                  block_residuals,
                  block_jacobians,
                  scratch->residual_block_evaluate_scratch.get())) {
            abort = true;
            return;
          }

          scratch->cost += block_cost;

          // Store the jacobians, if they were requested.
          if (jacobian != nullptr) {
            jacobian_writer_.Write(
                i, residual_layout_[i], block_jacobians, jacobian);
          }

          // Compute and store the gradient, if it was requested.
          if (gradient != nullptr) {
            int num_residuals = residual_block->NumResiduals();
            int num_parameter_blocks = residual_block->NumParameterBlocks();
            for (int j = 0; j < num_parameter_blocks; ++j) {
              const ParameterBlock* parameter_block =
                  residual_block->parameter_blocks()[j];
              if (parameter_block->IsConstant()) {
                continue;
              }

              MatrixTransposeVectorMultiply<Eigen::Dynamic, Eigen::Dynamic, 1>(
                  block_jacobians[j],
                  num_residuals,
                  parameter_block->TangentSize(),
                  block_residuals,
                  scratch->gradient.get() + parameter_block->delta_offset());
            }
          }
        });

    if (abort) {
      return false;
    }

    // Sum the cost and gradient (if requested) from each thread.
    (*cost) = 0.0;
    if (gradient != nullptr) {
      auto gradient_vector = VectorRef(gradient, num_parameters_);
      ParallelSetZero(options_.context, options_.num_threads, gradient_vector);
    }

    for (int i = 0; i < options_.num_threads; ++i) {
      (*cost) += evaluate_scratch_[i].cost;
      if (gradient != nullptr) {
        auto gradient_vector = VectorRef(gradient, num_parameters_);
        ParallelAssign(
            options_.context,
            options_.num_threads,
            gradient_vector,
            gradient_vector + VectorRef(evaluate_scratch_[i].gradient.get(),
                                        num_parameters_));
      }
    }

    // It is possible that after accumulation that the cost has become infinite
    // or a nan.
    if (!std::isfinite(*cost)) {
      LOG(ERROR) << "Accumulated cost = " << *cost
                 << " is not a finite number. Evaluation failed.";
      return false;
    }

    // Finalize the Jacobian if it is available.
    // `num_parameters` is passed to the finalizer so that additional
    // storage can be reserved for additional diagonal elements if
    // necessary.
    if (jacobian != nullptr) {
      JacobianFinalizer f;
      f(jacobian, num_parameters_);
    }

    return true;
  }
