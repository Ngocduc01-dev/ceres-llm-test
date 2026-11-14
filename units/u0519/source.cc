// u0519 – ceres::LineManifold::LineManifold<AmbientSpaceDimension>
// Trích từ include/ceres/line_manifold.h, dòng 129–139 (chỉ để xem, không compile)

template <int AmbientSpaceDimension>
LineManifold<AmbientSpaceDimension>::LineManifold(int size) : size_{size} {
  if (AmbientSpaceDimension != Eigen::Dynamic) {
    CHECK_EQ(AmbientSpaceDimension, size)
        << "Specified size by template parameter differs from the supplied "
           "one.";
  } else {
    CHECK_GT(size_, 1)
        << "The size of the manifold needs to be greater than 1.";
  }
}
