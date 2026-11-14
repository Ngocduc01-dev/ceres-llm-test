// u1170 – ceres::internal::EigenSparseCholeskyTemplate::Factorize
// Trích từ internal/ceres/eigensparse.cc, dòng 112–137 (chỉ để xem, không compile)

  LinearSolverTerminationType Factorize(CompressedRowSparseMatrix* lhs,
                                        std::string* message) final {
    CHECK_EQ(lhs->storage_type(), StorageType());

    typename Solver::Scalar* values_ptr = nullptr;
    if constexpr (std::is_same_v<typename Solver::Scalar, double>) {
      values_ptr = lhs->mutable_values();
    } else {
      // In the case where the scalar used in this class is not
      // double. In that case, make a copy of the values array in the
      // CompressedRowSparseMatrix and cast it to Scalar along the way.
      values_ = ConstVectorRef(lhs->values(), lhs->num_nonzeros())
                    .cast<typename Solver::Scalar>();
      values_ptr = values_.data();
    }

    Eigen::Map<
        const Eigen::SparseMatrix<typename Solver::Scalar, Eigen::ColMajor>>
        eigen_lhs(lhs->num_rows(),
                  lhs->num_rows(),
                  lhs->num_nonzeros(),
                  lhs->rows(),
                  lhs->cols(),
                  values_ptr);
    return Factorize(eigen_lhs, message);
  }
