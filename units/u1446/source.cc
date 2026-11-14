// u1446 – ceres::internal::CovarianceImpl::ComputeCovarianceSparsity
// Trích từ internal/ceres/covariance_impl.cc, dòng 360–498 (chỉ để xem, không compile)

bool CovarianceImpl::ComputeCovarianceSparsity(
    const CovarianceBlocks& original_covariance_blocks, ProblemImpl* problem) {
  EventLogger event_logger("CovarianceImpl::ComputeCovarianceSparsity");

  // Determine an ordering for the parameter block, by sorting the
  // parameter blocks by their pointers.
  std::vector<double*> all_parameter_blocks;
  problem->GetParameterBlocks(&all_parameter_blocks);
  const ProblemImpl::ParameterMap& parameter_map = problem->parameter_map();
  std::unordered_set<ParameterBlock*> parameter_blocks_in_use;
  std::vector<ResidualBlock*> residual_blocks;
  problem->GetResidualBlocks(&residual_blocks);

  for (auto* residual_block : residual_blocks) {
    parameter_blocks_in_use.insert(residual_block->parameter_blocks(),
                                   residual_block->parameter_blocks() +
                                       residual_block->NumParameterBlocks());
  }

  constant_parameter_blocks_.clear();
  std::vector<double*>& active_parameter_blocks =
      evaluate_options_.parameter_blocks;
  active_parameter_blocks.clear();
  for (auto* parameter_block : all_parameter_blocks) {
    ParameterBlock* block = FindOrDie(parameter_map, parameter_block);
    if (!block->IsConstant() && (parameter_blocks_in_use.count(block) > 0)) {
      active_parameter_blocks.push_back(parameter_block);
    } else {
      constant_parameter_blocks_.insert(parameter_block);
    }
  }

  std::sort(active_parameter_blocks.begin(), active_parameter_blocks.end());

  // Compute the number of rows.  Map each parameter block to the
  // first row corresponding to it in the covariance matrix using the
  // ordering of parameter blocks just constructed.
  int num_rows = 0;
  parameter_block_to_row_index_.clear();
  for (auto* parameter_block : active_parameter_blocks) {
    const int parameter_block_size =
        problem->ParameterBlockTangentSize(parameter_block);
    parameter_block_to_row_index_[parameter_block] = num_rows;
    num_rows += parameter_block_size;
  }

  // Compute the number of non-zeros in the covariance matrix.  Along
  // the way flip any covariance blocks which are in the lower
  // triangular part of the matrix.
  int num_nonzeros = 0;
  CovarianceBlocks covariance_blocks;
  for (const auto& block_pair : original_covariance_blocks) {
    if (constant_parameter_blocks_.count(block_pair.first) > 0 ||
        constant_parameter_blocks_.count(block_pair.second) > 0) {
      continue;
    }

    int index1 = FindOrDie(parameter_block_to_row_index_, block_pair.first);
    int index2 = FindOrDie(parameter_block_to_row_index_, block_pair.second);
    const int size1 = problem->ParameterBlockTangentSize(block_pair.first);
    const int size2 = problem->ParameterBlockTangentSize(block_pair.second);
    num_nonzeros += size1 * size2;

    // Make sure we are constructing a block upper triangular matrix.
    if (index1 > index2) {
      covariance_blocks.push_back(
          std::make_pair(block_pair.second, block_pair.first));
    } else {
      covariance_blocks.push_back(block_pair);
    }
  }

  if (covariance_blocks.empty()) {
    VLOG(2) << "No non-zero covariance blocks found";
    covariance_matrix_ = nullptr;
    return true;
  }

  // Sort the block pairs. As a consequence we get the covariance
  // blocks as they will occur in the CompressedRowSparseMatrix that
  // will store the covariance.
  std::sort(covariance_blocks.begin(), covariance_blocks.end());

  // Fill the sparsity pattern of the covariance matrix.
  covariance_matrix_ = std::make_unique<CompressedRowSparseMatrix>(
      num_rows, num_rows, num_nonzeros);

  int* rows = covariance_matrix_->mutable_rows();
  int* cols = covariance_matrix_->mutable_cols();

  // Iterate over parameter blocks and in turn over the rows of the
  // covariance matrix. For each parameter block, look in the upper
  // triangular part of the covariance matrix to see if there are any
  // blocks requested by the user. If this is the case then fill out a
  // set of compressed rows corresponding to this parameter block.
  //
  // The key thing that makes this loop work is the fact that the
  // row/columns of the covariance matrix are ordered by the pointer
  // values of the parameter blocks. Thus iterating over the keys of
  // parameter_block_to_row_index_ corresponds to iterating over the
  // rows of the covariance matrix in order.
  int i = 0;       // index into covariance_blocks.
  int cursor = 0;  // index into the covariance matrix.
  for (const auto& entry : parameter_block_to_row_index_) {
    const double* row_block = entry.first;
    const int row_block_size = problem->ParameterBlockTangentSize(row_block);
    int row_begin = entry.second;

    // Iterate over the covariance blocks contained in this row block
    // and count the number of columns in this row block.
    int num_col_blocks = 0;
    for (int j = i; j < covariance_blocks.size(); ++j, ++num_col_blocks) {
      const std::pair<const double*, const double*>& block_pair =
          covariance_blocks[j];
      if (block_pair.first != row_block) {
        break;
      }
    }

    // Fill out all the compressed rows for this parameter block.
    for (int r = 0; r < row_block_size; ++r) {
      rows[row_begin + r] = cursor;
      for (int c = 0; c < num_col_blocks; ++c) {
        const double* col_block = covariance_blocks[i + c].second;
        const int col_block_size =
            problem->ParameterBlockTangentSize(col_block);
        int col_begin = FindOrDie(parameter_block_to_row_index_, col_block);
        for (int k = 0; k < col_block_size; ++k) {
          cols[cursor++] = col_begin++;
        }
      }
    }

    i += num_col_blocks;
  }

  rows[num_rows] = cursor;
  return true;
}
