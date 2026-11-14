// u1238 – ceres::(anonymous)::EvaluateCostFunction
// Trích từ internal/ceres/gradient_checker.cc, dòng 55–113 (chỉ để xem, không compile)

bool EvaluateCostFunction(const CostFunction* function,
                          double const* const* parameters,
                          const std::vector<const Manifold*>& manifolds,
                          Vector* residuals,
                          std::vector<Matrix>* jacobians,
                          std::vector<Matrix>* local_jacobians) {
  CHECK(residuals != nullptr);
  CHECK(jacobians != nullptr);
  CHECK(local_jacobians != nullptr);

  const std::vector<int32_t>& block_sizes = function->parameter_block_sizes();
  const int num_parameter_blocks = block_sizes.size();

  // Allocate Jacobian matrices in tangent space.
  local_jacobians->resize(num_parameter_blocks);
  std::vector<double*> local_jacobian_data(num_parameter_blocks);
  for (int i = 0; i < num_parameter_blocks; ++i) {
    int block_size = block_sizes.at(i);
    if (manifolds.at(i) != nullptr) {
      block_size = manifolds.at(i)->TangentSize();
    }
    local_jacobians->at(i).resize(function->num_residuals(), block_size);
    local_jacobians->at(i).setZero();
    local_jacobian_data.at(i) = local_jacobians->at(i).data();
  }

  // Allocate Jacobian matrices in ambient space.
  jacobians->resize(num_parameter_blocks);
  std::vector<double*> jacobian_data(num_parameter_blocks);
  for (int i = 0; i < num_parameter_blocks; ++i) {
    jacobians->at(i).resize(function->num_residuals(), block_sizes.at(i));
    jacobians->at(i).setZero();
    jacobian_data.at(i) = jacobians->at(i).data();
  }

  // Compute residuals & jacobians.
  CHECK_NE(0, function->num_residuals());
  residuals->resize(function->num_residuals());
  residuals->setZero();
  if (!function->Evaluate(
          parameters, residuals->data(), jacobian_data.data())) {
    return false;
  }

  // Convert Jacobians from ambient to local space.
  for (size_t i = 0; i < local_jacobians->size(); ++i) {
    if (manifolds.at(i) == nullptr) {
      local_jacobians->at(i) = jacobians->at(i);
    } else {
      int ambient_size = manifolds.at(i)->AmbientSize();
      int tangent_size = manifolds.at(i)->TangentSize();
      CHECK_EQ(jacobians->at(i).cols(), ambient_size);
      Matrix ambient_J_tangent(ambient_size, tangent_size);
      manifolds.at(i)->PlusJacobian(parameters[i], ambient_J_tangent.data());
      local_jacobians->at(i).noalias() = jacobians->at(i) * ambient_J_tangent;
    }
  }
  return true;
}
