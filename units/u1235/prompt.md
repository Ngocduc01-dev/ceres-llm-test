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

- Hàm: `CreateStructureOfCompressedRowSparseMatrix(const double* values, int num_rows, int num_cols, int num_nonzeros, const CompressedRowBlockStructure* block_structure)`, trả về `std::unique_ptr<CompressedRowSparseMatrix>`
- Loại: hàm template (hàm mẫu, kiểu dữ liệu được điền khi dùng)
- Namespace: `ceres::internal::(namespace không tên)`
- Vị trí: `internal/ceres/block_sparse_matrix.cc`, dòng 67–118

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
 67 | template <bool transpose>
 68 | std::unique_ptr<CompressedRowSparseMatrix>
 69 | CreateStructureOfCompressedRowSparseMatrix(
 70 |     const double* values,
 71 |     int num_rows,
 72 |     int num_cols,
 73 |     int num_nonzeros,
 74 |     const CompressedRowBlockStructure* block_structure) {
 75 |   auto crs_matrix = std::make_unique<CompressedRowSparseMatrix>(
 76 |       num_rows, num_cols, num_nonzeros);
 77 |   auto crs_cols = crs_matrix->mutable_cols();
 78 |   auto crs_rows = crs_matrix->mutable_rows();
 79 |   int value_offset = 0;
 80 |   const int num_row_blocks = block_structure->rows.size();
 81 |   const auto& cols = block_structure->cols;
 82 |   *crs_rows++ = 0;
 83 |   for (int row_block_id = 0; row_block_id < num_row_blocks; ++row_block_id) {
 84 |     const auto& row_block = block_structure->rows[row_block_id];
 85 |     // Empty row block: only requires setting row offsets
 86 |     if (row_block.cells.empty()) {
 87 |       std::fill(crs_rows, crs_rows + row_block.block.size, value_offset);
 88 |       crs_rows += row_block.block.size;
 89 |       continue;
 90 |     }
 91 | 
 92 |     int row_nnz = 0;
 93 |     if constexpr (transpose) {
 94 |       // Transposed block structure comes with nnz in row-block filled-in
 95 |       row_nnz = row_block.nnz / row_block.block.size;
 96 |     } else {
 97 |       // Nnz field of non-transposed block structure is not filled and it can
 98 |       // have non-sequential structure (consider the case of jacobian for
 99 |       // Schur-complement solver: E and F blocks are stored separately).
100 |       for (auto& c : row_block.cells) {
101 |         row_nnz += cols[c.block_id].size;
102 |       }
103 |     }
104 | 
105 |     // Row-wise setup of matrix structure
106 |     for (int row = 0; row < row_block.block.size; ++row) {
107 |       value_offset += row_nnz;
108 |       *crs_rows++ = value_offset;
109 |       for (auto& c : row_block.cells) {
110 |         const int col_block_size = cols[c.block_id].size;
111 |         const int col_position = cols[c.block_id].position;
112 |         std::iota(crs_cols, crs_cols + col_block_size, col_position);
113 |         crs_cols += col_block_size;
114 |       }
115 |     }
116 |   }
117 |   return crs_matrix;
118 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Ghi chú: đây là template – một số kiểu dữ liệu còn để trống, chỉ được điền khi dùng. CFG dưới đây dựng cho trường hợp CreateStructureOfCompressedRowSparseMatrix<true> (lấy từ một chỗ Ceres dùng thật).

Số điểm rẽ nhánh: 4

START → 1
1   auto crs_cols = crs_matrix->mutable_cols()
    auto crs_rows = crs_matrix->mutable_rows()
    int value_offset = 0
    const int num_row_blocks = block_structure->rows.size()
    const auto &cols = block_structure->cols
    *crs_rows++ = 0
    int row_block_id = 0                                           → 2
2   vòng for, điều kiện: row_block_id < num_row_blocks             đúng → 3   sai → END
3   const auto &row_block = block_structure->rows[row_block_id]    → 4
4   if (row_block.cells.empty())                                   đúng → 5   sai → 7
5   std::fill(crs_rows, crs_rows + row_block.block.size, value_offset)
    crs_rows += row_block.block.size
    continue                                                       → 6
6   ++row_block_id                                                 → 2
7   int row_nnz = 0
    if true                                                        → 8
8   row_nnz = row_block.nnz / row_block.block.size                 → 9
9   int row = 0                                                    → 10
10  vòng for, điều kiện: row < row_block.block.size                đúng → 11   sai → 6
11  value_offset += row_nnz
    *crs_rows++ = value_offset                                     → 12
12  for (auto &c : row_block.cells)                                đúng → 13   sai → 15
13  auto &c
    const int col_block_size = cols[c.block_id].size
    const int col_position = cols[c.block_id].position
    std::iota(crs_cols, crs_cols + col_block_size, col_position)
    crs_cols += col_block_size                                     → 14
14  ++ (bước tiếp của vòng for)                                    → 12
15  ++row                                                          → 10
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
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/block_sparse_matrix.cc"
```

- Hàm này chỉ dùng được bên trong file `internal/ceres/block_sparse_matrix.cc` (khai báo `static` hoặc trong namespace không tên). Để gọi được, thêm `#include "ceres/block_sparse_matrix.cc"` vào file test.
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1235_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
