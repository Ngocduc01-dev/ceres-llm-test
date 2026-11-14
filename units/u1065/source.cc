// u1065 – ceres::internal::(anonymous)::CheckForNoAliasing
// Trích từ internal/ceres/problem_impl.cc, dòng 74–85 (chỉ để xem, không compile)

void CheckForNoAliasing(double* existing_block,
                        int existing_block_size,
                        double* new_block,
                        int new_block_size) {
  CHECK(!RegionsAlias(
      existing_block, existing_block_size, new_block, new_block_size))
      << "Aliasing detected between existing parameter block at memory "
      << "location " << existing_block << " and has size "
      << existing_block_size << " with new parameter "
      << "block that has memory address " << new_block << " and would have "
      << "size " << new_block_size << ".";
}
