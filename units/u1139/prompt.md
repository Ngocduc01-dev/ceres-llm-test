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

- Hàm: `NoEBlockRowOuterProduct(const BlockSparseMatrixData & A, int row_block_index, BlockRandomAccessMatrix * lhs)`, trả về `void`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::SchurEliminator` (class template)
- Vị trí: `internal/ceres/schur_eliminator_impl.h`, dòng 609–659

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
609 | template <int kRowBlockSize, int kEBlockSize, int kFBlockSize>
610 | void SchurEliminator<kRowBlockSize, kEBlockSize, kFBlockSize>::
611 |     NoEBlockRowOuterProduct(const BlockSparseMatrixData& A,
612 |                             int row_block_index,
613 |                             BlockRandomAccessMatrix* lhs) {
614 |   const CompressedRowBlockStructure* bs = A.block_structure();
615 |   const double* values = A.values();
616 | 
617 |   const CompressedRow& row = bs->rows[row_block_index];
618 |   for (int i = 0; i < row.cells.size(); ++i) {
619 |     const int block1 = row.cells[i].block_id - num_eliminate_blocks_;
620 |     DCHECK_GE(block1, 0);
621 | 
622 |     const int block1_size = bs->cols[row.cells[i].block_id].size;
623 |     int r, c, row_stride, col_stride;
624 |     CellInfo* cell_info =
625 |         lhs->GetCell(block1, block1, &r, &c, &row_stride, &col_stride);
626 |     if (cell_info != nullptr) {
627 |       auto lock = MakeConditionalLock(num_threads_, cell_info->m);
628 |       // This multiply currently ignores the fact that this is a
629 |       // symmetric outer product.
630 |       // clang-format off
631 |       MatrixTransposeMatrixMultiply
632 |           <Eigen::Dynamic, Eigen::Dynamic, Eigen::Dynamic, Eigen::Dynamic, 1>(
633 |               values + row.cells[i].position, row.block.size, block1_size,
634 |               values + row.cells[i].position, row.block.size, block1_size,
635 |               cell_info->values, r, c, row_stride, col_stride);
636 |       // clang-format on
637 |     }
638 | 
639 |     for (int j = i + 1; j < row.cells.size(); ++j) {
640 |       const int block2 = row.cells[j].block_id - num_eliminate_blocks_;
641 |       DCHECK_GE(block2, 0);
642 |       DCHECK_LT(block1, block2);
643 |       int r, c, row_stride, col_stride;
644 |       CellInfo* cell_info =
645 |           lhs->GetCell(block1, block2, &r, &c, &row_stride, &col_stride);
646 |       if (cell_info != nullptr) {
647 |         const int block2_size = bs->cols[row.cells[j].block_id].size;
648 |         auto lock = MakeConditionalLock(num_threads_, cell_info->m);
649 |         // clang-format off
650 |         MatrixTransposeMatrixMultiply
651 |             <Eigen::Dynamic, Eigen::Dynamic, Eigen::Dynamic, Eigen::Dynamic, 1>(
652 |                 values + row.cells[i].position, row.block.size, block1_size,
653 |                 values + row.cells[j].position, row.block.size, block2_size,
654 |                 cell_info->values, r, c, row_stride, col_stride);
655 |         // clang-format on
656 |       }
657 |     }
658 |   }
659 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Ghi chú: đây là template – một số kiểu dữ liệu còn để trống, chỉ được điền khi dùng. CFG dưới đây dựng cho trường hợp SchurEliminator<> (lấy từ một chỗ Ceres dùng thật).

Số điểm rẽ nhánh: 4 (và 3 lệnh CHECK)

START → 1
1   const CompressedRowBlockStructure *bs = A.block_structure()
    const double *values = A.values()
    const CompressedRow &row = bs->rows[row_block_index]
    int i = 0                                                      → 2
2   vòng for, điều kiện: i < row.cells.size()                      đúng → 3   sai → END
3   const int block1 = row.cells[i].block_id - num_eliminate_blocks_   → 4
4   DCHECK_GE(block1, 0)                                           đúng → 5   sai → DỪNG
5   const int block1_size = bs->cols[row.cells[i].block_id].size
    int r
    int c
    int row_stride
    int col_stride
    CellInfo *cell_info = lhs->GetCell(block1, block1, &r, &c, &row_stride, &col_stride)   → 6
6   if (cell_info != nullptr)                                      đúng → 7   sai → 8
7   MatrixTransposeMatrixMultiply<Eigen::Dynamic, Eigen::Dynamic, Eigen::Dynamic, Eigen::Dynamic, 1>(values + row.cells[i].position, row.block.size, block1_size, values + row.cells[i].position, row.block.size, block1_size, cell_info->values, r, c, row_stride, col_stride)   → 8
8   int j = i + 1                                                  → 9
9   vòng for, điều kiện: j < row.cells.size()                      đúng → 10   sai → 17
10  const int block2 = row.cells[j].block_id - num_eliminate_blocks_   → 11
11  DCHECK_GE(block2, 0)                                           đúng → 12   sai → DỪNG
12  DCHECK_LT(block1, block2)                                      đúng → 13   sai → DỪNG
13  int r
    int c
    int row_stride
    int col_stride
    CellInfo *cell_info = lhs->GetCell(block1, block2, &r, &c, &row_stride, &col_stride)   → 14
14  if (cell_info != nullptr)                                      đúng → 15   sai → 16
15  const int block2_size = bs->cols[row.cells[j].block_id].size
    MatrixTransposeMatrixMultiply<Eigen::Dynamic, Eigen::Dynamic, Eigen::Dynamic, Eigen::Dynamic, 1>(values + row.cells[i].position, row.block.size, block1_size, values + row.cells[j].position, row.block.size, block2_size, cell_info->values, r, c, row_stride, col_stride)   → 16
16  ++j                                                            → 9
17  ++i                                                            → 2
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
#include "ceres/block_random_access_matrix.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/parallel_for.h"
#include "ceres/schur_eliminator.h"
#include "ceres/schur_eliminator_impl.h"
#include "ceres/small_blas.h"
```

- Method này là `private` (bên ngoài class không gọi được). Thêm 2 dòng `#define private public` và `#define protected public` **sau** `#include "gtest/gtest.h"` và **trước** các `#include` của Ceres.
- Đây là method của class `ceres::internal::SchurEliminator`: tạo một object của class rồi gọi method trên object đó.
- Đây là template (khuôn mẫu): khi tạo object hoặc gọi hàm phải chọn kiểu cụ thể phù hợp (xem ví dụ chỗ dùng trong Ceres ở ghi chú của CFG, nếu có).

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1139_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
