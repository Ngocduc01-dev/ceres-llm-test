// u0214 – ceres::SphereManifold::SphereManifold<AmbientSpaceDimension>
// Trích từ include/ceres/sphere_manifold.h, dòng 136–142 (chỉ để xem, không compile)

template <int AmbientSpaceDimension>
SphereManifold<AmbientSpaceDimension>::SphereManifold()
    : size_{AmbientSpaceDimension} {
  static_assert(
      AmbientSpaceDimension != Eigen::Dynamic,
      "The size is set to dynamic. Please call the constructor with a size.");
}
