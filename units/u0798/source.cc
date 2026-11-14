// u0798 – ceres::ProductManifold::PlusJacobianImpl
// Trích từ include/ceres/product_manifold.h, dòng 199–218 (chỉ để xem, không compile)

  template <std::size_t Index0, std::size_t... Indices>
  bool PlusJacobianImpl(const double* x,
                        MatrixRef& jacobian,
                        internal::FixedArray<double>& buffer,
                        std::index_sequence<Index0, Indices...>) const {
    if (!Dereference(std::get<Index0>(manifolds_))
             .PlusJacobian(x + ambient_offsets_[Index0], buffer.data())) {
      return false;
    }

    jacobian.block(ambient_offsets_[Index0],
                   tangent_offsets_[Index0],
                   ambient_sizes_[Index0],
                   tangent_sizes_[Index0]) =
        MatrixRef(
            buffer.data(), ambient_sizes_[Index0], tangent_sizes_[Index0]);

    return PlusJacobianImpl(
        x, jacobian, buffer, std::index_sequence<Indices...>{});
  }
