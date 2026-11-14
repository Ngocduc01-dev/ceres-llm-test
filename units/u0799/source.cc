// u0799 – ceres::ProductManifold::MinusJacobianImpl
// Trích từ include/ceres/product_manifold.h, dòng 228–247 (chỉ để xem, không compile)

  template <std::size_t Index0, std::size_t... Indices>
  bool MinusJacobianImpl(const double* x,
                         MatrixRef& jacobian,
                         internal::FixedArray<double>& buffer,
                         std::index_sequence<Index0, Indices...>) const {
    if (!Dereference(std::get<Index0>(manifolds_))
             .MinusJacobian(x + ambient_offsets_[Index0], buffer.data())) {
      return false;
    }

    jacobian.block(tangent_offsets_[Index0],
                   ambient_offsets_[Index0],
                   tangent_sizes_[Index0],
                   ambient_sizes_[Index0]) =
        MatrixRef(
            buffer.data(), tangent_sizes_[Index0], ambient_sizes_[Index0]);

    return MinusJacobianImpl(
        x, jacobian, buffer, std::index_sequence<Indices...>{});
  }
