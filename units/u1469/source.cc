// u1469 – ceres::internal::CovarianceImpl::GetCovarianceMatrixInTangentOrAmbientSpace
// Trích từ internal/ceres/covariance_impl.cc, dòng 276–356 (chỉ để xem, không compile)

bool CovarianceImpl::GetCovarianceMatrixInTangentOrAmbientSpace(
    const std::vector<const double*>& parameters,
    bool lift_covariance_to_ambient_space,
    double* covariance_matrix) const {
  CHECK(is_computed_)
      << "Covariance::GetCovarianceMatrix called before Covariance::Compute";
  CHECK(is_valid_)
      << "Covariance::GetCovarianceMatrix called when Covariance::Compute "
      << "returned false.";

  const ProblemImpl::ParameterMap& parameter_map = problem_->parameter_map();
  // For OpenMP compatibility we need to define these vectors in advance
  const int num_parameters = parameters.size();
  std::vector<int> parameter_sizes;
  std::vector<int> cum_parameter_size;
  parameter_sizes.reserve(num_parameters);
  cum_parameter_size.resize(num_parameters + 1);
  cum_parameter_size[0] = 0;
  for (int i = 0; i < num_parameters; ++i) {
    ParameterBlock* block =
        FindOrDie(parameter_map, const_cast<double*>(parameters[i]));
    if (lift_covariance_to_ambient_space) {
      parameter_sizes.push_back(block->Size());
    } else {
      parameter_sizes.push_back(block->TangentSize());
    }
  }
  std::partial_sum(parameter_sizes.begin(),
                   parameter_sizes.end(),
                   cum_parameter_size.begin() + 1);
  const int max_covariance_block_size =
      *std::max_element(parameter_sizes.begin(), parameter_sizes.end());
  const int covariance_size = cum_parameter_size.back();

  // Assemble the blocks in the covariance matrix.
  MatrixRef covariance(covariance_matrix, covariance_size, covariance_size);
  const int num_threads = options_.num_threads;
  auto workspace = std::make_unique<double[]>(
      num_threads * max_covariance_block_size * max_covariance_block_size);

  bool success = true;

  // Technically the following code is a double nested loop where
  // i = 1:n, j = i:n.
  int iteration_count = (num_parameters * (num_parameters + 1)) / 2;
  problem_->context()->EnsureMinimumThreads(num_threads);
  ParallelFor(problem_->context(),
              0,
              iteration_count,
              num_threads,
              [&](int thread_id, int k) {
                int i, j;
                LinearIndexToUpperTriangularIndex(k, num_parameters, &i, &j);

                int covariance_row_idx = cum_parameter_size[i];
                int covariance_col_idx = cum_parameter_size[j];
                int size_i = parameter_sizes[i];
                int size_j = parameter_sizes[j];
                double* covariance_block =
                    workspace.get() + thread_id * max_covariance_block_size *
                                          max_covariance_block_size;
                if (!GetCovarianceBlockInTangentOrAmbientSpace(
                        parameters[i],
                        parameters[j],
                        lift_covariance_to_ambient_space,
                        covariance_block)) {
                  success = false;
                }

                covariance.block(
                    covariance_row_idx, covariance_col_idx, size_i, size_j) =
                    MatrixRef(covariance_block, size_i, size_j);

                if (i != j) {
                  covariance.block(
                      covariance_col_idx, covariance_row_idx, size_j, size_i) =
                      MatrixRef(covariance_block, size_i, size_j).transpose();
                }
              });
  return success;
}
