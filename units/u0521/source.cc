// u0521 – ceres::EuclideanManifold::EuclideanManifold<Size>
// Trích từ include/ceres/manifold.h, dòng 254–263 (chỉ để xem, không compile)

  explicit EuclideanManifold(int size) : size_(size) {
    if (Size != ceres::DYNAMIC) {
      CHECK_EQ(Size, size)
          << "Specified size by template parameter differs from the supplied "
             "one.";
    } else {
      CHECK_GE(size_, 0)
          << "The size of the manifold needs to be non-negative.";
    }
  }
