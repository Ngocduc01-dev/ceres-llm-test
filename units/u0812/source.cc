// u0812 – ceres::internal::VisibilityBasedPreconditioner::FlattenMembershipMap
// Trích từ internal/ceres/visibility_based_preconditioner.cc, dòng 536–572 (chỉ để xem, không compile)

void VisibilityBasedPreconditioner::FlattenMembershipMap(
    const std::unordered_map<int, int>& membership_map,
    std::vector<int>* membership_vector) const {
  CHECK(membership_vector != nullptr);
  membership_vector->resize(0);
  membership_vector->resize(num_blocks_, -1);

  std::unordered_map<int, int> cluster_id_to_index;
  // Iterate over the cluster membership map and update the
  // cluster_membership_ vector assigning arbitrary cluster ids to
  // the few cameras that have not been clustered.
  for (const auto& m : membership_map) {
    const int camera_id = m.first;
    int cluster_id = m.second;

    // If the view was not clustered, randomly assign it to one of the
    // clusters. This preserves the mathematical correctness of the
    // preconditioner. If there are too many views which are not
    // clustered, it may lead to some quality degradation though.
    //
    // TODO(sameeragarwal): Check if a large number of views have not
    // been clustered and deal with it?
    if (cluster_id == -1) {
      cluster_id = camera_id % num_clusters_;
    }

    const int index = FindWithDefault(
        cluster_id_to_index, cluster_id, cluster_id_to_index.size());

    if (index == cluster_id_to_index.size()) {
      cluster_id_to_index[cluster_id] = index;
    }

    CHECK_LT(index, num_clusters_);
    membership_vector->at(camera_id) = index;
  }
}
