**A. Test paths**

Có 3 điểm rẽ nhánh (node 3, 7, 9), tức 6 nhánh. CFG khớp với mã nguồn. Cả hai vòng `for` chạy đúng `num_rows()` lần, nên số lần lặp bằng số hàng n.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → 6 → 7 → 12 → 13 → END | node 1: đúng; node 3: sai (0 lần lặp); node 7: sai (0 lần lặp); node 13: đúng |
| P2 | START → 1 → 2 → (3 → 4 → 5)×1 → 3 → 6 → (7 → 8 → 9 → 10 → 11)×1 → 7 → 12 → 13 → END | node 3: đúng 1 lần rồi sai; node 7: đúng 1 lần rồi sai; node 9: đúng |
| P3 | Như P2 nhưng vòng 3 và vòng 7 lặp 2 lần, lần 1 đi qua 9 → 11 | node 3, 7: đúng 2 lần rồi sai; node 9: sai (lần 1), đúng (lần 2) |
| P4 | Như P3 nhưng lặp 3 lần | node 3, 7: đúng 3 lần rồi sai; node 9: đúng, sai, đúng |
| P5 | Như P3 nhưng lặp 4 lần (n−1) | node 3, 7: đúng 4 lần rồi sai; node 9: đúng, sai, đúng, đúng |
| P6 | Như P3 nhưng lặp 5 lần (n) | node 3, 7: đúng 5 lần rồi sai; node 9: đúng ở cả 5 lần |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | num_rows = 0; `num_additional_elements` ∈ [0, 5] | rows=0, cols=3, additional=2 |
| TC2 | P2 | num_rows = 1; hàng 0 có ≥1 phần tử; additional ∈ [0, 5] | rows=1, cols=3; hàng 0: (0,1)=1.5; additional=0 |
| TC3 | P3 | num_rows = 2; hàng 0 rỗng, hàng 1 có ≥1 phần tử | rows=2, cols=4; hàng 1: (1,0)=2.0, (1,3)=3.0; additional=3 |
| TC4 | P4 | num_rows = 3; hàng 1 rỗng (giá trị giữa) | rows=3, cols=4; hàng 0: (0,2)=1.0; hàng 2: (2,1)=4.0; additional=1 |
| TC5 | P5 | num_rows = 4; hàng 1 rỗng, các hàng còn lại có phần tử | rows=4, cols=5; (0,0)=1.0, (2,4)=2.0, (3,1)=3.0; additional=5 |
| TC6 | P6 | num_rows = 5; mọi hàng có phần tử | rows=5, cols=5; (i, i)=i+1 với i=0..4; additional=4 |

**C. Nhánh không test**

- node 1 sai (`CHECK_GE` sai): không test (làm chương trình dừng).
- node 13 sai (`CHECK_EQ` sai): không test (làm chương trình dừng). Nhánh này cũng không thể đi tới vì `index_into_values_and_cols` luôn bằng tổng kích thước các `dynamic_cols_[i]`.
- Hai nhánh CHECK không tính vào tổng số nhánh.
- n+1 lần lặp không làm được, vì số lần lặp đúng bằng `num_rows()`, nên không thể vượt n.
- Để nạp dữ liệu vào `dynamic_cols_`, test dùng `InsertEntry(row, col, value)` của class. Tên này không có trong đoạn mã đã cho, nhưng nó là public method của class và cần thiết để tạo dữ liệu.

`C2 dự kiến = 6 / 6` (dự kiến, chưa chạy thật)

**D. File test**

```cpp
// FILE: u1119_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/dynamic_compressed_row_sparse_matrix.h"

namespace ceres {
namespace internal {

// P1: node 1: đúng, node 3: sai (0 lần), node 7: sai (0 lần), node 13: đúng
TEST(DynamicCompressedRowSparseMatrixFinalize, ZeroRows) {
  DynamicCompressedRowSparseMatrix m(0, 3, 0);
  m.Finalize(2);
}

// P2: node 3: đúng x1 rồi sai, node 7: đúng x1 rồi sai, node 9: đúng
TEST(DynamicCompressedRowSparseMatrixFinalize, OneRowWithEntry) {
  DynamicCompressedRowSparseMatrix m(1, 3, 1);
  m.InsertEntry(0, 1, 1.5);
  m.Finalize(0);
}

// P3: node 3, 7: đúng x2 rồi sai; node 9: sai (hàng 0), đúng (hàng 1)
TEST(DynamicCompressedRowSparseMatrixFinalize, TwoRowsFirstEmpty) {
  DynamicCompressedRowSparseMatrix m(2, 4, 2);
  m.InsertEntry(1, 0, 2.0);
  m.InsertEntry(1, 3, 3.0);
  m.Finalize(3);
}

// P4: node 3, 7: đúng x3 rồi sai; node 9: đúng, sai, đúng
TEST(DynamicCompressedRowSparseMatrixFinalize, ThreeRowsMiddleEmpty) {
  DynamicCompressedRowSparseMatrix m(3, 4, 2);
  m.InsertEntry(0, 2, 1.0);
  m.InsertEntry(2, 1, 4.0);
  m.Finalize(1);
}

// P5: node 3, 7: đúng x4 (n-1) rồi sai; node 9: đúng, sai, đúng, đúng
TEST(DynamicCompressedRowSparseMatrixFinalize, FourRowsOneEmpty) {
  DynamicCompressedRowSparseMatrix m(4, 5, 3);
  m.InsertEntry(0, 0, 1.0);
  m.InsertEntry(2, 4, 2.0);
  m.InsertEntry(3, 1, 3.0);
  m.Finalize(5);
}

// P6: node 3, 7: đúng x5 (n) rồi sai; node 9: đúng ở cả 5 hàng
TEST(DynamicCompressedRowSparseMatrixFinalize, FiveRowsAllNonEmpty) {
  DynamicCompressedRowSparseMatrix m(5, 5, 5);
  for (int i = 0; i < 5; ++i) {
    m.InsertEntry(i, i, static_cast<double>(i + 1));
  }
  m.Finalize(4);
}

}  // namespace internal
}  // namespace ceres
```