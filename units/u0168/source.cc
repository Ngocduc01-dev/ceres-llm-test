// u0168 – ceres::LineManifold::LineManifold<AmbientSpaceDimension>
// Trích từ include/ceres/line_manifold.h, dòng 121–127 (chỉ để xem, không compile)

template <int AmbientSpaceDimension>
LineManifold<AmbientSpaceDimension>::LineManifold()
    : size_{AmbientSpaceDimension} {
  static_assert(
      AmbientSpaceDimension != Eigen::Dynamic,
      "The size is set to dynamic. Please call the constructor with a size.");
}
