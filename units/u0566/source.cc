// u0566 – ceres::ProductManifold::ProductManifold<Manifold0, Manifold1, ManifoldN...>
// Trích từ include/ceres/product_manifold.h, dòng 138–153 (chỉ để xem, không compile)

  template <std::size_t... Indices, typename... Args>
  explicit ProductManifold(std::index_sequence<Indices...>, Args&&... manifolds)
      : manifolds_{std::forward<Args>(manifolds)...},
        buffer_size_{(std::max)(
            {(Dereference(std::get<Indices>(manifolds_)).TangentSize() *
              Dereference(std::get<Indices>(manifolds_)).AmbientSize())...})},
        ambient_sizes_{
            Dereference(std::get<Indices>(manifolds_)).AmbientSize()...},
        tangent_sizes_{
            Dereference(std::get<Indices>(manifolds_)).TangentSize()...},
        ambient_offsets_{ExclusiveScan(ambient_sizes_)},
        tangent_offsets_{ExclusiveScan(tangent_sizes_)},
        ambient_size_{
            std::accumulate(ambient_sizes_.begin(), ambient_sizes_.end(), 0)},
        tangent_size_{
            std::accumulate(tangent_sizes_.begin(), tangent_sizes_.end(), 0)} {}
