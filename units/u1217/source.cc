// u1217 – ceres::internal::CovarianceImpl::GetCovarianceBlockInTangentOrAmbientSpace
// Trích từ internal/ceres/covariance_impl.cc, dòng 128–274 (chỉ để xem, không compile)

bool CovarianceImpl::GetCovarianceBlockInTangentOrAmbientSpace(
    const double* original_parameter_block1,
    const double* original_parameter_block2,
    bool lift_covariance_to_ambient_space,
    double* covariance_block) const {
  CHECK(is_computed_)
      << "Covariance::GetCovarianceBlock called before Covariance::Compute";
  CHECK(is_valid_)
      << "Covariance::GetCovarianceBlock called when Covariance::Compute "
      << "returned false.";

  // If either of the two parameter blocks is constant, then the
  // covariance block is also zero.
  if (constant_parameter_blocks_.count(original_parameter_block1) > 0 ||
      constant_parameter_blocks_.count(original_parameter_block2) > 0) {
    const ProblemImpl::ParameterMap& parameter_map = problem_->parameter_map();
    ParameterBlock* block1 = FindOrDie(
        parameter_map, const_cast<double*>(original_parameter_block1));

    ParameterBlock* block2 = FindOrDie(
        parameter_map, const_cast<double*>(original_parameter_block2));

    const int block1_size = block1->Size();
    const int block2_size = block2->Size();
    const int block1_tangent_size = block1->TangentSize();
    const int block2_tangent_size = block2->TangentSize();
    if (!lift_covariance_to_ambient_space) {
      MatrixRef(covariance_block, block1_tangent_size, block2_tangent_size)
          .setZero();
    } else {
      MatrixRef(covariance_block, block1_size, block2_size).setZero();
    }
    return true;
  }

  const double* parameter_block1 = original_parameter_block1;
  const double* parameter_block2 = original_parameter_block2;
  const bool transpose = parameter_block1 > parameter_block2;
  if (transpose) {
    std::swap(parameter_block1, parameter_block2);
  }

  // Find where in the covariance matrix the block is located.
  const int row_begin =
      FindOrDie(parameter_block_to_row_index_, parameter_block1);
  const int col_begin =
      FindOrDie(parameter_block_to_row_index_, parameter_block2);
  const int* rows = covariance_matrix_->rows();
  const int* cols = covariance_matrix_->cols();
  const int row_size = rows[row_begin + 1] - rows[row_begin];
  const int* cols_begin = cols + rows[row_begin];

  // The only part that requires work is walking the compressed column
  // vector to determine where the set of columns corresponding to the
  // covariance block begin.
  int offset = 0;
  while (cols_begin[offset] != col_begin && offset < row_size) {
    ++offset;
  }

  if (offset == row_size) {
    LOG(ERROR) << "Unable to find covariance block for "
               << original_parameter_block1 << " " << original_parameter_block2;
    return false;
  }

  const ProblemImpl::ParameterMap& parameter_map = problem_->parameter_map();
  ParameterBlock* block1 =
      FindOrDie(parameter_map, const_cast<double*>(parameter_block1));
  ParameterBlock* block2 =
      FindOrDie(parameter_map, const_cast<double*>(parameter_block2));
  const Manifold* manifold1 = block1->manifold();
  const Manifold* manifold2 = block2->manifold();
  const int block1_size = block1->Size();
  const int block1_tangent_size = block1->TangentSize();
  const int block2_size = block2->Size();
  const int block2_tangent_size = block2->TangentSize();

  ConstMatrixRef cov(covariance_matrix_->values() + rows[row_begin],
                     block1_tangent_size,
                     row_size);

  // Fast path when there are no manifolds or if the user does not want it
  // lifted to the ambient space.
  if ((manifold1 == nullptr && manifold2 == nullptr) ||
      !lift_covariance_to_ambient_space) {
    if (transpose) {
      MatrixRef(covariance_block, block2_tangent_size, block1_tangent_size) =
          cov.block(0, offset, block1_tangent_size, block2_tangent_size)
              .transpose();
    } else {
      MatrixRef(covariance_block, block1_tangent_size, block2_tangent_size) =
          cov.block(0, offset, block1_tangent_size, block2_tangent_size);
    }
    return true;
  }

  // If manifolds are used then the covariance that has been computed is in the
  // tangent space and it needs to be lifted back to the ambient space.
  //
  // This is given by the formula
  //
  //  C'_12 = J_1 C_12 J_2'
  //
  // Where C_12 is the local tangent space covariance for parameter
  // blocks 1 and 2. J_1 and J_2 are respectively the local to global
  // jacobians for parameter blocks 1 and 2.
  //
  // See Result 5.11 on page 142 of Hartley & Zisserman (2nd Edition)
  // for a proof.
  //
  // TODO(sameeragarwal): Add caching the manifold plus_jacobian, so that they
  // are computed just once per parameter block.
  Matrix block1_jacobian(block1_size, block1_tangent_size);
  if (manifold1 == nullptr) {
    block1_jacobian.setIdentity();
  } else {
    manifold1->PlusJacobian(parameter_block1, block1_jacobian.data());
  }

  Matrix block2_jacobian(block2_size, block2_tangent_size);
  // Fast path if the user is requesting a diagonal block.
  if (parameter_block1 == parameter_block2) {
    block2_jacobian = block1_jacobian;
  } else {
    if (manifold2 == nullptr) {
      block2_jacobian.setIdentity();
    } else {
      manifold2->PlusJacobian(parameter_block2, block2_jacobian.data());
    }
  }

  if (transpose) {
    MatrixRef(covariance_block, block2_size, block1_size) =
        block2_jacobian *
        cov.block(0, offset, block1_tangent_size, block2_tangent_size)
            .transpose() *
        block1_jacobian.transpose();
  } else {
    MatrixRef(covariance_block, block1_size, block2_size) =
        block1_jacobian *
        cov.block(0, offset, block1_tangent_size, block2_tangent_size) *
        block2_jacobian.transpose();
  }

  return true;
}
