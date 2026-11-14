// u0785 – ceres::internal::DetectStructure
// Trích từ internal/ceres/detect_structure.cc, dòng 38–119 (chỉ để xem, không compile)

void DetectStructure(const CompressedRowBlockStructure& bs,
                     const int num_eliminate_blocks,
                     int* row_block_size,
                     int* e_block_size,
                     int* f_block_size) {
  const int num_row_blocks = bs.rows.size();
  *row_block_size = 0;
  *e_block_size = 0;
  *f_block_size = 0;

  // Iterate over row blocks of the matrix, checking if row_block,
  // e_block or f_block sizes remain constant.
  for (int r = 0; r < num_row_blocks; ++r) {
    const CompressedRow& row = bs.rows[r];
    // We do not care about the sizes of the blocks in rows which do
    // not contain e_blocks.
    if (row.cells.front().block_id >= num_eliminate_blocks) {
      break;
    }

    // Detect fixed or dynamic row block size.
    if (*row_block_size == 0) {
      *row_block_size = row.block.size;
    } else if (*row_block_size != Eigen::Dynamic &&
               *row_block_size != row.block.size) {
      VLOG(2) << "Dynamic row block size because the block size changed from "
              << *row_block_size << " to " << row.block.size;
      *row_block_size = Eigen::Dynamic;
    }

    // Detect fixed or dynamic e-block size.
    const int e_block_id = row.cells.front().block_id;
    if (*e_block_size == 0) {
      *e_block_size = bs.cols[e_block_id].size;
    } else if (*e_block_size != Eigen::Dynamic &&
               *e_block_size != bs.cols[e_block_id].size) {
      VLOG(2) << "Dynamic e block size because the block size changed from "
              << *e_block_size << " to " << bs.cols[e_block_id].size;
      *e_block_size = Eigen::Dynamic;
    }

    // Detect fixed or dynamic f-block size. We are only interested in
    // rows with e-blocks, and the e-block is always the first block,
    // so only rows of size greater than 1 are of interest.
    if (row.cells.size() > 1) {
      if (*f_block_size == 0) {
        const int f_block_id = row.cells[1].block_id;
        *f_block_size = bs.cols[f_block_id].size;
      }

      for (int c = 1;
           (c < row.cells.size()) && (*f_block_size != Eigen::Dynamic);
           ++c) {
        const int f_block_id = row.cells[c].block_id;
        if (*f_block_size != bs.cols[f_block_id].size) {
          VLOG(2) << "Dynamic f block size because the block size "
                  << "changed from " << *f_block_size << " to "
                  << bs.cols[f_block_id].size;
          *f_block_size = Eigen::Dynamic;
        }
      }
    }

    // clang-format off
    const bool is_everything_dynamic = (*row_block_size == Eigen::Dynamic &&
                                        *e_block_size == Eigen::Dynamic &&
                                        *f_block_size == Eigen::Dynamic);
    // clang-format on
    if (is_everything_dynamic) {
      break;
    }
  }

  CHECK_NE(*row_block_size, 0) << "No rows found";
  CHECK_NE(*e_block_size, 0) << "No e type blocks found";
  // clang-format off
  VLOG(1) << "Schur complement static structure <"
          << *row_block_size << ","
          << *e_block_size << ","
          << *f_block_size << ">.";
  // clang-format on
}
