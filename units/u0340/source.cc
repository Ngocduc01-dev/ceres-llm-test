// u0340 – ceres::SubsetManifold::AmbientSize
// Trích từ internal/ceres/manifold.cc, dòng 181–181 (chỉ để xem, không compile)

int SubsetManifold::AmbientSize() const { return constancy_mask_.size(); }
