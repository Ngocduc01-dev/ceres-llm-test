// u1275 – ceres::(anonymous)::SchurStructureToString
// Trích từ internal/ceres/solver.cc, dòng 656–672 (chỉ để xem, không compile)

std::string SchurStructureToString(const int row_block_size,
                                   const int e_block_size,
                                   const int f_block_size) {
  const std::string row = (row_block_size == Eigen::Dynamic)
                              ? "d"
                              : internal::StringPrintf("%d", row_block_size);

  const std::string e = (e_block_size == Eigen::Dynamic)
                            ? "d"
                            : internal::StringPrintf("%d", e_block_size);

  const std::string f = (f_block_size == Eigen::Dynamic)
                            ? "d"
                            : internal::StringPrintf("%d", f_block_size);

  return internal::StringPrintf("%s,%s,%s", row.c_str(), e.c_str(), f.c_str());
}
