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

- Hàm: `CreateRandomMatrix(const BlockSparseMatrix::RandomMatrixOptions & options, std::mt19937 & prng, bool use_page_locked_memory)`, trả về `std::unique_ptr<BlockSparseMatrix>`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::BlockSparseMatrix`
- Vị trí: `internal/ceres/block_sparse_matrix.cc`, dòng 711–781

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
711 | std::unique_ptr<BlockSparseMatrix> BlockSparseMatrix::CreateRandomMatrix(
712 |     const BlockSparseMatrix::RandomMatrixOptions& options,
713 |     std::mt19937& prng,
714 |     bool use_page_locked_memory) {
715 |   CHECK_GT(options.num_row_blocks, 0);
716 |   CHECK_GT(options.min_row_block_size, 0);
717 |   CHECK_GT(options.max_row_block_size, 0);
718 |   CHECK_LE(options.min_row_block_size, options.max_row_block_size);
719 |   CHECK_GT(options.block_density, 0.0);
720 |   CHECK_LE(options.block_density, 1.0);
721 | 
722 |   std::uniform_int_distribution<int> col_distribution(
723 |       options.min_col_block_size, options.max_col_block_size);
724 |   std::uniform_int_distribution<int> row_distribution(
725 |       options.min_row_block_size, options.max_row_block_size);
726 |   auto bs = std::make_unique<CompressedRowBlockStructure>();
727 |   if (options.col_blocks.empty()) {
728 |     CHECK_GT(options.num_col_blocks, 0);
729 |     CHECK_GT(options.min_col_block_size, 0);
730 |     CHECK_GT(options.max_col_block_size, 0);
731 |     CHECK_LE(options.min_col_block_size, options.max_col_block_size);
732 | 
733 |     // Generate the col block structure.
734 |     int col_block_position = 0;
735 |     for (int i = 0; i < options.num_col_blocks; ++i) {
736 |       const int col_block_size = col_distribution(prng);
737 |       bs->cols.emplace_back(col_block_size, col_block_position);
738 |       col_block_position += col_block_size;
739 |     }
740 |   } else {
741 |     bs->cols = options.col_blocks;
742 |   }
743 | 
744 |   bool matrix_has_blocks = false;
745 |   std::uniform_real_distribution<double> uniform01(0.0, 1.0);
746 |   while (!matrix_has_blocks) {
747 |     VLOG(1) << "Clearing";
748 |     bs->rows.clear();
749 |     int row_block_position = 0;
750 |     int value_position = 0;
751 |     for (int r = 0; r < options.num_row_blocks; ++r) {
752 |       const int row_block_size = row_distribution(prng);
753 |       bs->rows.emplace_back();
754 |       CompressedRow& row = bs->rows.back();
755 |       row.block.size = row_block_size;
756 |       row.block.position = row_block_position;
757 |       row_block_position += row_block_size;
758 |       for (int c = 0; c < bs->cols.size(); ++c) {
759 |         if (uniform01(prng) > options.block_density) continue;
760 | 
761 |         row.cells.emplace_back();
762 |         Cell& cell = row.cells.back();
763 |         cell.block_id = c;
764 |         cell.position = value_position;
765 |         value_position += row_block_size * bs->cols[c].size;
766 |         matrix_has_blocks = true;
767 |       }
768 |     }
769 |   }
770 | 
771 |   auto matrix =
772 |       std::make_unique<BlockSparseMatrix>(bs.release(), use_page_locked_memory);
773 |   double* values = matrix->mutable_values();
774 |   std::normal_distribution<double> standard_normal_distribution;
775 |   std::generate_n(
776 |       values, matrix->num_nonzeros(), [&standard_normal_distribution, &prng] {
777 |         return standard_normal_distribution(prng);
778 |       });
779 | 
780 |   return matrix;
781 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 6 (và 10 lệnh CHECK)

START → 1
1   CHECK_GT(options.num_row_blocks, 0)                            đúng → 2   sai → DỪNG
2   CHECK_GT(options.min_row_block_size, 0)                        đúng → 3   sai → DỪNG
3   CHECK_GT(options.max_row_block_size, 0)                        đúng → 4   sai → DỪNG
4   CHECK_LE(options.min_row_block_size, options.max_row_block_size)   đúng → 5   sai → DỪNG
5   CHECK_GT(options.block_density, 0.0)                           đúng → 6   sai → DỪNG
6   CHECK_LE(options.block_density, 1.0)                           đúng → 7   sai → DỪNG
7   options.min_col_block_size, options.max_col_block_size
    options.min_row_block_size, options.max_row_block_size         → 8
8   if (options.col_blocks.empty())                                đúng → 9   sai → 28
9   CHECK_GT(options.num_col_blocks, 0)                            đúng → 10   sai → DỪNG
10  CHECK_GT(options.min_col_block_size, 0)                        đúng → 11   sai → DỪNG
11  CHECK_GT(options.max_col_block_size, 0)                        đúng → 12   sai → DỪNG
12  CHECK_LE(options.min_col_block_size, options.max_col_block_size)   đúng → 13   sai → DỪNG
13  int col_block_position = 0
    int i = 0                                                      → 14
14  vòng for, điều kiện: i < options.num_col_blocks                đúng → 15   sai → 17
15  const int col_block_size = col_distribution(prng)
    bs->cols.emplace_back(col_block_size, col_block_position)
    col_block_position += col_block_size                           → 16
16  ++i                                                            → 14
17  bool matrix_has_blocks = false
    0., 1.                                                         → 18
18  while (!matrix_has_blocks)                                     đúng → 19   sai → 27
19  vòng for, điều kiện: r < options.num_row_blocks                đúng → 20   sai → 18
20  const int row_block_size = row_distribution(prng)
    bs->rows.emplace_back()
    CompressedRow &row = bs->rows.back()
    row.block.size = row_block_size
    row.block.position = row_block_position
    row_block_position += row_block_size
    int c = 0                                                      → 21
21  vòng for, điều kiện: c < bs->cols.size()                       đúng → 22   sai → 26
22  if (uniform01(prng) > options.block_density)                   đúng → 23   sai → 25
23  continue                                                       → 24
24  ++c                                                            → 21
25  row.cells.emplace_back()
    Cell &cell = row.cells.back()
    cell.block_id = c
    cell.position = value_position
    value_position += row_block_size * bs->cols[c].size
    matrix_has_blocks = true                                       → 24
26  ++r                                                            → 19
27  double *values = matrix->mutable_values()
    std::generate_n (ImplicitCastExpr, FunctionToPointerDecay, double *(*)(double *, int, class (lambda at /work/ceres-solver/internal/ceres/block_sparse_matrix.cc:776:39)))(values, matrix->num_nonzeros(), [&standard_normal_distribution, &prng] {)   → END
28  bs->cols = options.col_blocks                                  → 17
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1218_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
