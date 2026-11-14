// u0198 – ceres::ProductManifold::ProductManifold<Manifold0, Manifold1, ManifoldN...>
// Trích từ include/ceres/product_manifold.h, dòng 92–98 (chỉ để xem, không compile)

  template <typename... Args,
            std::enable_if_t<std::is_constructible<
                std::tuple<Manifold0, Manifold1, ManifoldN...>,
                Args...>::value>* = nullptr>
  explicit ProductManifold(Args&&... manifolds)
      : ProductManifold{std::make_index_sequence<kNumManifolds>{},
                        std::forward<Args>(manifolds)...} {}
