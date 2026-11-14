// u0522 – ceres::SphereManifold::SphereManifold<AmbientSpaceDimension>
// Trích từ include/ceres/sphere_manifold.h, dòng 144–154 (chỉ để xem, không compile)

template <int AmbientSpaceDimension>
SphereManifold<AmbientSpaceDimension>::SphereManifold(int size) : size_{size} {
  if (AmbientSpaceDimension != Eigen::Dynamic) {
    CHECK_EQ(AmbientSpaceDimension, size)
        << "Specified size by template parameter differs from the supplied "
           "one.";
  } else {
    CHECK_GT(size_, 1)
        << "The size of the manifold needs to be greater than 1.";
  }
}
