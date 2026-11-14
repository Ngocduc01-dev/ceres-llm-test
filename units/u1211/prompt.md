# 1. NHIỆM VỤ

Bạn là kỹ sư kiểm thử phần mềm. Hãy thiết kế bộ test cho **một hàm C++** (gọi là **unit**) ở mục 3 theo phương pháp **kiểm thử luồng điều khiển (CFT)**, sao cho đạt **độ phủ nhánh C2**, rồi viết bộ test đó thành **một file GoogleTest** (thư viện viết unit test cho C++) chạy được.

- Dự án: thư viện **Ceres Solver 2.2.0**, viết bằng C++17.
- Dự án **không có tài liệu mô tả kết quả đúng**, nên **không cần kiểm tra kết quả trả về**. Mục tiêu chỉ là gọi hàm sao cho chương trình **đi qua đủ các nhánh**.

---

# 2. KHÁI NIỆM CẦN DÙNG

- **CFG (đồ thị luồng điều khiển):** sơ đồ các bước của hàm. Mỗi **node** là một đoạn lệnh chạy liền nhau hoặc một chỗ rẽ nhánh; mũi tên nối các node theo thứ tự chạy.
- **Điểm rẽ nhánh:** chỗ chương trình chọn đường đi theo một điều kiện: `if`, `else if`, vòng `for` / `while`, `switch`, `?:`. Mỗi điểm rẽ nhánh có **2 nhánh**: điều kiện **đúng** và điều kiện **sai** (`switch` có 1 nhánh cho mỗi `case`).
- **Độ phủ C2 (phủ nhánh):** mọi nhánh của mọi điểm rẽ nhánh đều được chạy qua ít nhất 1 lần.
  **C2 = số nhánh đã chạy qua / tổng số nhánh × 100%.**
  (C2 chặt hơn C1 – chỉ yêu cầu mỗi câu lệnh chạy ít nhất 1 lần. Ví dụ `if (x > 0) y = 1;`: chỉ cần x > 0 là đạt C1, nhưng C2 cần thêm 1 test với x ≤ 0.)
  Điều kiện ghép như `a && b`, `a || b` được tính là **một** điểm rẽ nhánh.
- **Test path (đường kiểm thử):** một đường đi trên CFG, từ `START` tới `END`, ghi rõ ở mỗi điểm rẽ nhánh đi theo nhánh nào.
- **Điều kiện của đường đi:** các điều kiện phải đúng/sai dọc theo một test path. Dữ liệu đầu vào của test phải thoả các điều kiện này.
- **Nhánh không thể đi tới:** nhánh mà không có dữ liệu nào làm chương trình đi vào (ví dụ điều kiện mâu thuẫn). Ghi rõ lý do, vẫn tính vào tổng số nhánh.
- **Vòng lặp:**
  - Có giới hạn số lần lặp n (ví dụ `for (i = 0; i < size; ...)`): test với **0, 1, 2, một số ở giữa, n−1, n** lần lặp; thêm **n+1** nếu làm được.
  - Không có giới hạn (lặp đến khi thoả một điều kiện, ví dụ `while (!done)`): test với **0, 1, 2** lần lặp và **mỗi cách thoát khỏi vòng lặp** (`break`, `return`, điều kiện sai) ít nhất 1 lần.
  - Số lần lặp nào không làm được thì ghi lý do.
- **`CHECK(...)`:** lệnh kiểm tra của thư viện glog mà Ceres dùng. Nếu điều kiện sai, chương trình **dừng ngay**. **Không** cố tình làm `CHECK` sai; ghi nhánh đó là "không test (làm chương trình dừng)".

---

# 3. ĐẦU VÀO

## 3.1. Unit cần test

- Hàm: `AppendRows(const BlockSparseMatrix & m)`, trả về `void`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::BlockSparseMatrix`
- Vị trí: `internal/ceres/block_sparse_matrix.cc`, dòng 616–667

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
616 | void BlockSparseMatrix::AppendRows(const BlockSparseMatrix& m) {
617 |   CHECK_EQ(m.num_cols(), num_cols());
618 |   const CompressedRowBlockStructure* m_bs = m.block_structure();
619 |   CHECK_EQ(m_bs->cols.size(), block_structure_->cols.size());
620 | 
621 |   const int old_num_nonzeros = num_nonzeros_;
622 |   const int old_num_row_blocks = block_structure_->rows.size();
623 |   block_structure_->rows.resize(old_num_row_blocks + m_bs->rows.size());
624 | 
625 |   for (int i = 0; i < m_bs->rows.size(); ++i) {
626 |     const CompressedRow& m_row = m_bs->rows[i];
627 |     const int row_block_id = old_num_row_blocks + i;
628 |     CompressedRow& row = block_structure_->rows[row_block_id];
629 |     row.block.size = m_row.block.size;
630 |     row.block.position = num_rows_;
631 |     num_rows_ += m_row.block.size;
632 |     row.cells.resize(m_row.cells.size());
633 |     if (transpose_block_structure_) {
634 |       transpose_block_structure_->cols.emplace_back(row.block);
635 |     }
636 |     for (int c = 0; c < m_row.cells.size(); ++c) {
637 |       const int block_id = m_row.cells[c].block_id;
638 |       row.cells[c].block_id = block_id;
639 |       row.cells[c].position = num_nonzeros_;
640 | 
641 |       const int cell_nnz = m_row.block.size * m_bs->cols[block_id].size;
642 |       if (transpose_block_structure_) {
643 |         transpose_block_structure_->rows[block_id].cells.emplace_back(
644 |             row_block_id, num_nonzeros_);
645 |         transpose_block_structure_->rows[block_id].nnz += cell_nnz;
646 |       }
647 | 
648 |       num_nonzeros_ += cell_nnz;
649 |     }
650 |   }
651 | 
652 |   if (num_nonzeros_ > max_num_nonzeros_) {
653 |     double* old_values = values_;
654 |     values_ = AllocateValues(num_nonzeros_);
655 |     std::copy_n(old_values, old_num_nonzeros, values_);
656 |     max_num_nonzeros_ = num_nonzeros_;
657 |     FreeValues(old_values);
658 |   }
659 | 
660 |   std::copy(
661 |       m.values(), m.values() + m.num_nonzeros(), values_ + old_num_nonzeros);
662 | 
663 |   if (transpose_block_structure_ == nullptr) {
664 |     return;
665 |   }
666 |   ComputeCumulativeNumberOfNonZeros(transpose_block_structure_->rows);
667 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 6 (và 2 lệnh CHECK)

START → 1
1   CHECK_EQ(m.num_cols(), num_cols())                             đúng → 2   sai → DỪNG
2   const CompressedRowBlockStructure *m_bs = m.block_structure()   → 3
3   CHECK_EQ(m_bs->cols.size(), block_structure_->cols.size())     đúng → 4   sai → DỪNG
4   const int old_num_nonzeros = num_nonzeros_
    const int old_num_row_blocks = block_structure_->rows.size()
    block_structure_->rows.resize(old_num_row_blocks + m_bs->rows.size())
    int i = 0                                                      → 5
5   vòng for, điều kiện: i < m_bs->rows.size()                     đúng → 6   sai → 17
6   const CompressedRow &m_row = m_bs->rows[i]
    const int row_block_id = old_num_row_blocks + i
    CompressedRow &row = block_structure_->rows[row_block_id]
    row.block.size = m_row.block.size
    row.block.position = num_rows_
    num_rows_ += m_row.block.size
    row.cells.resize(m_row.cells.size())                           → 7
7   if (transpose_block_structure_)                                đúng → 8   sai → 9
8   transpose_block_structure_->cols.emplace_back(row.block)       → 9
9   int c = 0                                                      → 10
10  vòng for, điều kiện: c < m_row.cells.size()                    đúng → 11   sai → 16
11  const int block_id = m_row.cells[c].block_id
    row.cells[c].block_id = block_id
    row.cells[c].position = num_nonzeros_
    const int cell_nnz = m_row.block.size * m_bs->cols[block_id].size   → 12
12  if (transpose_block_structure_)                                đúng → 13   sai → 14
13  transpose_block_structure_->rows[block_id].cells.emplace_back(row_block_id, num_nonzeros_)
    transpose_block_structure_->rows[block_id].nnz += cell_nnz     → 14
14  num_nonzeros_ += cell_nnz                                      → 15
15  ++c                                                            → 10
16  ++i                                                            → 5
17  if (num_nonzeros_ > max_num_nonzeros_)                         đúng → 18   sai → 19
18  double *old_values = values_
    values_ = AllocateValues(num_nonzeros_)
    std::copy_n(old_values, old_num_nonzeros, values_)
    max_num_nonzeros_ = num_nonzeros_
    FreeValues(old_values)                                         → 19
19  std::copy(m.values(), m.values() + m.num_nonzeros(), values_ + old_num_nonzeros)   → 20
20  if (transpose_block_structure_ == nullptr)                     đúng → 21   sai → 22
21  return                                                         → END
22  ComputeCumulativeNumberOfNonZeros(transpose_block_structure_->rows)   → END
```

**Cách đọc:** dòng đầu cho biết hàm có bao nhiêu điểm rẽ nhánh. Mỗi dòng sau đó là **một node**: số node, nội dung (câu lệnh hoặc điều kiện), rồi mũi tên tới node tiếp theo. Dòng "Ghi chú" (nếu có) cho biết unit là template và CFG được dựng với kiểu dữ liệu cụ thể nào.
- Node có điều kiện ghi `đúng → x   sai → y`: điều kiện đúng thì đi tới node x, sai thì đi tới node y.
- `START`: bắt đầu hàm · `END`: kết thúc hàm · `DỪNG`: chương trình dừng do `CHECK` sai.
- Nếu thấy CFG không khớp với mã nguồn, **tin mã nguồn** và ghi chú lại.
- Khi trả lời, gọi các node bằng **đúng số node này**.

## 3.3. Cách gọi unit trong file test

Các dòng `#include` được dùng:
```cpp
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
```

- Đây là method của class `ceres::internal::BlockSparseMatrix`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `BlockSparseMatrix`:
Các constructor:
```cpp
  BlockSparseMatrix(CompressedRowBlockStructure * block_structure, bool use_page_locked_memory)
```

---

# 4. YÊU CẦU ĐỐI VỚI BỘ TEST

1. Mỗi nhánh (đúng và sai) của mỗi điểm rẽ nhánh có **ít nhất 1 test** đi qua.
2. Mỗi vòng lặp được test với số lần lặp như mục 2.
3. Mỗi test ứng với **một test path**, ghi rõ các nhánh nó đi qua (ví dụ `node 2: đúng, node 4: sai`).
4. Dùng **ít test nhất** có thể: một test nên đi qua nhiều nhánh chưa được phủ.
5. **Dữ liệu đầu vào:** từ điều kiện của đường đi, xác định **khoảng giá trị** hợp lệ cho từng đầu vào (ví dụ `n` từ 1 đến 5), rồi **chọn ngẫu nhiên một giá trị** trong khoảng đó. Nếu dùng hàm sinh số ngẫu nhiên trong code thì **cố định giá trị khởi tạo (seed)** để mỗi lần chạy ra cùng một giá trị. Mảng, ma trận nhỏ (tối đa 5 phần tử). Không dùng file, mạng, đa luồng.
6. **Không** kiểm tra kết quả trả về (không có kết quả đúng để so).

---

# 5. CÁC BƯỚC THỰC HIỆN

1. Đọc mã nguồn và CFG của unit.
2. Liệt kê các điểm rẽ nhánh và các nhánh cần phủ.
3. Chọn các test path sao cho phủ hết các nhánh (trừ nhánh không thể đi tới và nhánh `CHECK` sai).
4. Với mỗi test path: viết điều kiện của đường đi → khoảng giá trị đầu vào → chọn giá trị ngẫu nhiên trong khoảng.
5. Viết code GoogleTest: mỗi test chuẩn bị dữ liệu rồi gọi unit **một lần**.
6. Kiểm tra lại: mọi nhánh đã có test chưa, code có dùng đúng tên hàm và `#include` ở mục 3.3 không.

---

# 6. KẾT QUẢ CẦN TRẢ VỀ

**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → … → END | node 1: đúng, node 2: sai |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | … | … |

**C. Nhánh không test** (nếu có): nhánh nào, vì sao. Kèm 1 dòng: `C2 dự kiến = <số nhánh có test> / <tổng số nhánh>` (dự kiến, chưa chạy thật).

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1211_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
