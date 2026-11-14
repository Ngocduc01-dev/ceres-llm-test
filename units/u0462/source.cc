// u0462 – ceres::SphereManifold::AmbientSize
// Trích từ include/ceres/sphere_manifold.h, dòng 97–100 (chỉ để xem, không compile)

  int AmbientSize() const override {
    return AmbientSpaceDimension == ceres::DYNAMIC ? size_
                                                   : AmbientSpaceDimension;
  }
