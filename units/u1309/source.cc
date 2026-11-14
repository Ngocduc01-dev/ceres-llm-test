// u1309 – ceres::internal::ProgramEvaluator::BuildResidualLayout
// Trích từ internal/ceres/program_evaluator.h, dòng 347–358 (chỉ để xem, không compile)

  static void BuildResidualLayout(const Program& program,
                                  std::vector<int>* residual_layout) {
    const std::vector<ResidualBlock*>& residual_blocks =
        program.residual_blocks();
    residual_layout->resize(program.NumResidualBlocks());
    int residual_pos = 0;
    for (int i = 0; i < residual_blocks.size(); ++i) {
      const int num_residuals = residual_blocks[i]->NumResiduals();
      (*residual_layout)[i] = residual_pos;
      residual_pos += num_residuals;
    }
  }
