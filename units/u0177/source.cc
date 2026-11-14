// u0177 – ceres::EuclideanManifold::EuclideanManifold<Size>
// Trích từ include/ceres/manifold.h, dòng 248–252 (chỉ để xem, không compile)

  EuclideanManifold() : size_{Size} {
    static_assert(
        Size != ceres::DYNAMIC,
        "The size is set to dynamic. Please call the constructor with a size.");
  }
