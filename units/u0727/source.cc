// u0727 – ceres::internal::InnerProductComputer::ProductTerm::operator<
// Trích từ internal/ceres/inner_product_computer.h, dòng 109–117 (chỉ để xem, không compile)

    bool operator<(const ProductTerm& right) const {
      if (row == right.row) {
        if (col == right.col) {
          return index < right.index;
        }
        return col < right.col;
      }
      return row < right.row;
    }
