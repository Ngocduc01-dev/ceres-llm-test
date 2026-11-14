// u0724 – ceres::internal::FloatEigenSparseCholesky::Create
// Trích từ internal/ceres/eigensparse.cc, dòng 176–201 (chỉ để xem, không compile)

std::unique_ptr<SparseCholesky> FloatEigenSparseCholesky::Create(
    const OrderingType ordering_type) {
  using WithAMDOrdering = Eigen::SimplicialLDLT<Eigen::SparseMatrix<float>,
                                                Eigen::Upper,
                                                Eigen::AMDOrdering<int>>;
  using WithNaturalOrdering =
      Eigen::SimplicialLDLT<Eigen::SparseMatrix<float>,
                            Eigen::Upper,
                            Eigen::NaturalOrdering<int>>;
  if (ordering_type == OrderingType::AMD) {
    return std::make_unique<EigenSparseCholeskyTemplate<WithAMDOrdering>>();
  } else if (ordering_type == OrderingType::NESDIS) {
#ifndef CERES_NO_EIGEN_METIS
    using WithMetisOrdering = Eigen::SimplicialLDLT<Eigen::SparseMatrix<float>,
                                                    Eigen::Upper,
                                                    Eigen::MetisOrdering<int>>;
    return std::make_unique<EigenSparseCholeskyTemplate<WithMetisOrdering>>();
#else
    LOG(FATAL)
        << "Congratulations you have found a bug in Ceres Solver. Please "
           "report it to the Ceres Solver developers.";
    return nullptr;
#endif  // CERES_NO_EIGEN_METIS
  }
  return std::make_unique<EigenSparseCholeskyTemplate<WithNaturalOrdering>>();
}
