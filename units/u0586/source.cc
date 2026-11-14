// u0586 – ceres::ProductManifold::PlusImpl
// Trích từ include/ceres/product_manifold.h, dòng 155–168 (chỉ để xem, không compile)

  template <std::size_t Index0, std::size_t... Indices>
  bool PlusImpl(const double* x,
                const double* delta,
                double* x_plus_delta,
                std::index_sequence<Index0, Indices...>) const {
    if (!Dereference(std::get<Index0>(manifolds_))
             .Plus(x + ambient_offsets_[Index0],
                   delta + tangent_offsets_[Index0],
                   x_plus_delta + ambient_offsets_[Index0])) {
      return false;
    }

    return PlusImpl(x, delta, x_plus_delta, std::index_sequence<Indices...>{});
  }
