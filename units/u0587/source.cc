// u0587 – ceres::ProductManifold::MinusImpl
// Trích từ include/ceres/product_manifold.h, dòng 177–190 (chỉ để xem, không compile)

  template <std::size_t Index0, std::size_t... Indices>
  bool MinusImpl(const double* y,
                 const double* x,
                 double* y_minus_x,
                 std::index_sequence<Index0, Indices...>) const {
    if (!Dereference(std::get<Index0>(manifolds_))
             .Minus(y + ambient_offsets_[Index0],
                    x + ambient_offsets_[Index0],
                    y_minus_x + tangent_offsets_[Index0])) {
      return false;
    }

    return MinusImpl(y, x, y_minus_x, std::index_sequence<Indices...>{});
  }
