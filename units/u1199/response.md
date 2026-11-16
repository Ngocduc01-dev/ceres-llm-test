**A. Test paths**

Có 4 điểm rẽ nhánh (node 2, 4, 6, 8), tổng 8 nhánh. CFG khớp với mã nguồn.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 14 → END | node 1: đúng; node 2: sai (0 lần lặp vòng ngoài) |
| P2 | START → 1 → 2 → 3 → 4 → 13 → 2 → 14 → END | node 2: đúng, rồi sai; node 4: sai (0 cell) |
| P3 | START → 1 → 2 → 3 → 4 → 5 → 6 → 7 → 8 → 9 → 10 → 8 → 11 → 6 → 12 → 4 → 13 → 2 → 14 → END | node 2: đúng, rồi sai; node 4: đúng, rồi sai; node 6: đúng, rồi sai; node 8: đúng, rồi sai (mỗi vòng lặp 1 lần) |
| P4 | START → 1 → 2 → [3 → 4 → (5 → 6 → (7 → 8 → 9 → 10 → 8)×2 → 11 → 6)×2 → 12 → 4 → …] → 13 → 2 → … → 14 → END | node 2, 4, 6, 8 đều đúng rồi sai; vòng ngoài 2 lần, vòng cell 2 lần, vòng r 2 lần, vòng c 2 lần |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `rows.size() = 0` | 0 hàng, 1 cột (size 1) |
| TC2 | P2 | `rows.size() = 1`, `cells.size() = 0` | 1 hàng (size 1), 0 cell |
| TC3 | P3 | 1 hàng, 1 cell, `row_block_size = 1`, `col_block_size = 1` | 1 hàng, 1 cell, kích thước khối 1×1 |
| TC4 | P4 | `rows.size() = 2`; hàng 0 có 2 cell; `row_block_size` ≥ 2; `col_block_size` ≥ 2 với ít nhất 1 cột | Hàng 0: size 2, cell vào cột 0 (size 2) và cột 1 (size 1); hàng 1: size 1, 1 cell vào cột 1 |

Dữ liệu cố định, không dùng số ngẫu nhiên, nên mỗi lần chạy cho cùng kết quả.

**C. Nhánh không test**

- `CHECK(matrix != nullptr)` sai (node 1): không test vì làm chương trình dừng. Nhánh này không nằm trong tổng số nhánh.
- Vòng lặp node 6 và node 8 với 0 lần lặp: không test vì khối có kích thước 0 không xảy ra trong thực tế.
- Số lần lặp "n−1, n, n+1" của vòng ngoài: dữ liệu giới hạn tối đa 5 phần tử nên chỉ test 0, 1, 2 lần lặp (TC4 dùng toàn bộ n = 2 hàng).

C2 dự kiến = 8 / 8

**D. File test**

```cpp
// FILE: u1199_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/triplet_sparse_matrix.h"

namespace ceres {
namespace internal {

// P1: node 1: đúng, node 2: sai (0 hàng)
TEST(BlockSparseMatrixToTriplet, NoRows) {
  auto* bs = new CompressedRowBlockStructure;
  bs->cols.emplace_back();
  bs->cols[0].size = 1;
  bs->cols[0].position = 0;
  BlockSparseMatrix m(bs, false);
  TripletSparseMatrix t;
  m.ToTripletSparseMatrix(&t);
}

// P2: node 2: đúng rồi sai, node 4: sai (hàng không có cell)
TEST(BlockSparseMatrixToTriplet, OneRowNoCells) {
  auto* bs = new CompressedRowBlockStructure;
  bs->cols.emplace_back();
  bs->cols[0].size = 1;
  bs->cols[0].position = 0;
  bs->rows.emplace_back();
  bs->rows[0].block.size = 1;
  bs->rows[0].block.position = 0;
  BlockSparseMatrix m(bs, false);
  TripletSparseMatrix t;
  m.ToTripletSparseMatrix(&t);
}

// P3: node 2, 4, 6, 8: đúng rồi sai (mỗi vòng lặp 1 lần)
TEST(BlockSparseMatrixToTriplet, OneRowOneCell1x1) {
  auto* bs = new CompressedRowBlockStructure;
  bs->cols.emplace_back();
  bs->cols[0].size = 1;
  bs->cols[0].position = 0;
  bs->rows.emplace_back();
  bs->rows[0].block.size = 1;
  bs->rows[0].block.position = 0;
  bs->rows[0].cells.emplace_back(0, 0);
  BlockSparseMatrix m(bs, false);
  TripletSparseMatrix t;
  m.ToTripletSparseMatrix(&t);
}

// P4: node 2, 4, 6, 8: đúng rồi sai (mỗi vòng lặp 2 lần)
TEST(BlockSparseMatrixToTriplet, TwoRowsMultipleCells) {
  auto* bs = new CompressedRowBlockStructure;
  bs->cols.emplace_back();
  bs->cols[0].size = 2;
  bs->cols[0].position = 0;
  bs->cols.emplace_back();
  bs->cols[1].size = 1;
  bs->cols[1].position = 2;

  bs->rows.emplace_back();
  bs->rows[0].block.size = 2;
  bs->rows[0].block.position = 0;
  bs->rows[0].cells.emplace_back(0, 0);  // 2x2 = 4 giá trị
  bs->rows[0].cells.emplace_back(1, 4);  // 2x1 = 2 giá trị

  bs->rows.emplace_back();
  bs->rows[1].block.size = 1;
  bs->rows[1].block.position = 2;
  bs->rows[1].cells.emplace_back(1, 6);  // 1x1 = 1 giá trị

  BlockSparseMatrix m(bs, false);
  TripletSparseMatrix t;
  m.ToTripletSparseMatrix(&t);
}

}  // namespace internal
}  // namespace ceres
```