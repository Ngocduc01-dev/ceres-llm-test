# 1. NHIỆM VỤ

Bạn là kỹ sư kiểm thử phần mềm. Hãy thiết kế bộ test cho **một hàm C++** (gọi là **unit**) ở mục 3 theo phương pháp **kiểm thử luồng điều khiển (CFT)**, sao cho đạt **độ phủ nhánh C2**, rồi viết bộ test đó thành **một file GoogleTest** (thư viện viết unit test cho C++) chạy được.

- Dự án: thư viện **Ceres Solver 2.2.0**, viết bằng C++17.
- Dự án **không có tài liệu mô tả kết quả đúng**, nên **không cần kiểm tra kết quả trả về**. Mục tiêu chỉ là gọi hàm sao cho chương trình **đi qua đủ các nhánh**.

---

# 2. KHÁI NIỆM

- **CFG (đồ thị luồng điều khiển):** sơ đồ các bước của hàm. Mỗi **node** là một đoạn lệnh chạy liền nhau hoặc một chỗ rẽ nhánh; mũi tên nối các node theo thứ tự chạy.
- **Điểm rẽ nhánh:** chỗ chương trình chọn đường đi theo một điều kiện: `if`, `else if`, vòng `for` / `while`, `switch`, `?:`. Mỗi điểm rẽ nhánh có **2 nhánh**: điều kiện **đúng** và điều kiện **sai** (`switch` có 1 nhánh cho mỗi `case`).
- **Độ phủ C2 (phủ nhánh):** mọi nhánh của mọi điểm rẽ nhánh đều được chạy qua ít nhất 1 lần.
  **C2 = số nhánh đã chạy qua / tổng số nhánh × 100%.**
  (C2 chặt hơn C1 – chỉ yêu cầu mỗi câu lệnh chạy ít nhất 1 lần. Ví dụ `if (x > 0) y = 1;`: chỉ cần x > 0 là đạt C1, nhưng C2 cần thêm 1 test với x ≤ 0.)
  Điều kiện ghép như `a && b`, `a || b` được tính là **một** điểm rẽ nhánh.
- **Test path (đường kiểm thử):** một đường đi trên CFG, từ `START` tới `END`, ghi rõ ở mỗi điểm rẽ nhánh đi theo nhánh nào.
- **Điều kiện của đường đi:** các điều kiện phải đúng/sai dọc theo một test path. Dữ liệu đầu vào của test phải thoả các điều kiện này.
- **Nhánh không thể đi tới:** nhánh mà không có dữ liệu nào làm chương trình đi vào (ví dụ điều kiện mâu thuẫn). Ghi rõ lý do, vẫn tính vào tổng số nhánh.
- **Tổng số nhánh** (mẫu số của C2) = 2 × số điểm rẽ nhánh ghi ở dòng đầu CFG (`switch`: mỗi `case` là 1 nhánh). **Không** tính nhánh của `CHECK`.
- **Vòng lặp:**
  - Có giới hạn số lần lặp n (ví dụ `for (i = 0; i < size; ...)`): test với **0, 1, 2, một số ở giữa, n−1, n** lần lặp; thêm **n+1** nếu làm được.
  - Không có giới hạn (lặp đến khi thoả một điều kiện, ví dụ `while (!done)`): test với **0, 1, 2** lần lặp và **mỗi cách thoát khỏi vòng lặp** (`break`, `return`, điều kiện sai) ít nhất 1 lần.
  - Số lần lặp nào không làm được thì ghi lý do.
- **`CHECK(...)`:** lệnh kiểm tra của thư viện glog mà Ceres dùng. Nếu điều kiện sai, chương trình **dừng ngay**. **Không** cố tình làm `CHECK` sai; ghi nhánh đó là "không test (làm chương trình dừng)".

---

# 3. ĐẦU VÀO

## 3.1. Unit cần test

- Hàm: `PartitionedMatrixView(const LinearSolver::Options & options, const BlockSparseMatrix & matrix)`
- Loại: constructor (hàm khởi tạo)
- Thuộc class: `ceres::internal::PartitionedMatrixView` (class template)
- Vị trí: `internal/ceres/partitioned_matrix_view_impl.h`, dòng 47–105

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
 47 | template <int kRowBlockSize, int kEBlockSize, int kFBlockSize>
 48 | PartitionedMatrixView<kRowBlockSize, kEBlockSize, kFBlockSize>::
 49 |     PartitionedMatrixView(const LinearSolver::Options& options,
 50 |                           const BlockSparseMatrix& matrix)
 51 | 
 52 |     : options_(options), matrix_(matrix) {
 53 |   const CompressedRowBlockStructure* bs = matrix_.block_structure();
 54 |   CHECK(bs != nullptr);
 55 | 
 56 |   num_col_blocks_e_ = options_.elimination_groups[0];
 57 |   num_col_blocks_f_ = bs->cols.size() - num_col_blocks_e_;
 58 | 
 59 |   // Compute the number of row blocks in E. The number of row blocks
 60 |   // in E maybe less than the number of row blocks in the input matrix
 61 |   // as some of the row blocks at the bottom may not have any
 62 |   // e_blocks. For a definition of what an e_block is, please see
 63 |   // schur_complement_solver.h
 64 |   num_row_blocks_e_ = 0;
 65 |   for (const auto& row : bs->rows) {
 66 |     const std::vector<Cell>& cells = row.cells;
 67 |     if (cells[0].block_id < num_col_blocks_e_) {
 68 |       ++num_row_blocks_e_;
 69 |     }
 70 |   }
 71 | 
 72 |   // Compute the number of columns in E and F.
 73 |   num_cols_e_ = 0;
 74 |   num_cols_f_ = 0;
 75 | 
 76 |   for (int c = 0; c < bs->cols.size(); ++c) {
 77 |     const Block& block = bs->cols[c];
 78 |     if (c < num_col_blocks_e_) {
 79 |       num_cols_e_ += block.size;
 80 |     } else {
 81 |       num_cols_f_ += block.size;
 82 |     }
 83 |   }
 84 | 
 85 |   CHECK_EQ(num_cols_e_ + num_cols_f_, matrix_.num_cols());
 86 | 
 87 |   auto transpose_bs = matrix_.transpose_block_structure();
 88 |   const int num_threads = options_.num_threads;
 89 |   if (transpose_bs != nullptr && num_threads > 1) {
 90 |     int kMaxPartitions = num_threads * 4;
 91 |     e_cols_partition_ = PartitionRangeForParallelFor(
 92 |         0,
 93 |         num_col_blocks_e_,
 94 |         kMaxPartitions,
 95 |         transpose_bs->rows.data(),
 96 |         [](const CompressedRow& row) { return row.cumulative_nnz; });
 97 | 
 98 |     f_cols_partition_ = PartitionRangeForParallelFor(
 99 |         num_col_blocks_e_,
100 |         num_col_blocks_e_ + num_col_blocks_f_,
101 |         kMaxPartitions,
102 |         transpose_bs->rows.data(),
103 |         [](const CompressedRow& row) { return row.cumulative_nnz; });
104 |   }
105 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Ghi chú: đây là template – một số kiểu dữ liệu còn để trống, chỉ được điền khi dùng. CFG dưới đây dựng cho trường hợp PartitionedMatrixView<>.

Số điểm rẽ nhánh: 5 (và 2 lệnh CHECK)

START → 1
1   PartitionedMatrixViewBase() (Base initializer)
    options_(options) (Member initializer)
    matrix_(matrix) (Member initializer)
    e_cols_partition_() (Member initializer)
    f_cols_partition_() (Member initializer)
    const CompressedRowBlockStructure *bs = matrix_.block_structure()   → 2
2   CHECK(bs != nullptr)                                           đúng → 3   sai → DỪNG
3   for (const auto &row : bs->rows)                               đúng → 4   sai → 8
4   const auto &row
    const std::vector<Cell> &cells = row.cells                     → 5
5   if (cells[0].block_id < num_col_blocks_e_)                     đúng → 6   sai → 7
6   ++num_row_blocks_e_                                            → 7
7   ++ (bước tiếp của vòng for)                                    → 3
8   num_cols_e_ = 0
    num_cols_f_ = 0
    int c = 0                                                      → 9
9   vòng for, điều kiện: c < bs->cols.size()                       đúng → 10   sai → 15
10  const Block &block = bs->cols[c]                               → 11
11  if (c < num_col_blocks_e_)                                     đúng → 12   sai → 14
12  num_cols_e_ += block.size                                      → 13
13  ++c                                                            → 9
14  num_cols_f_ += block.size                                      → 13
15  CHECK_EQ(num_cols_e_ + num_cols_f_, matrix_.num_cols())        đúng → 16   sai → DỪNG
16  auto transpose_bs = matrix_.transpose_block_structure()
    const int num_threads = options_.num_threads                   → 17
17  if (transpose_bs != nullptr && num_threads > 1)                đúng → 18   sai → END
18  int kMaxPartitions = num_threads * 4
    operator= (ImplicitCastExpr, FunctionToPointerDecay, vector<int> &(*)(vector<int> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    e_cols_partition_ = PartitionRangeForParallelFor (ImplicitCastExpr, FunctionToPointerDecay, std::vector<int> (*)(int, int, int, const struct ceres::internal::CompressedList *, class (lambda at /work/ceres-solver/internal/ceres/partitioned_matrix_view_impl.h:96:9) &&))(0, num_col_blocks_e_, kMaxPartitions, transpose_bs->rows.data(), [](const CompressedRow &row) {)
    operator= (ImplicitCastExpr, FunctionToPointerDecay, vector<int> &(*)(vector<int> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    f_cols_partition_ = PartitionRangeForParallelFor (ImplicitCastExpr, FunctionToPointerDecay, std::vector<int> (*)(int, int, int, const struct ceres::internal::CompressedList *, class (lambda at /work/ceres-solver/internal/ceres/partitioned_matrix_view_impl.h:103:9) &&))(num_col_blocks_e_, num_col_blocks_e_ + num_col_blocks_f_, kMaxPartitions, transpose_bs->rows.data(), [](const CompressedRow &row) {)   → END
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
#include "ceres/linear_solver.h"
#include "ceres/partitioned_matrix_view.h"
#include "ceres/partitioned_matrix_view_impl.h"
```

- Đây là method của class `ceres::internal::PartitionedMatrixView`: tạo một object của class rồi gọi method trên object đó.
- Đây là template (khuôn mẫu): khi tạo object hoặc gọi hàm phải chọn kiểu cụ thể phù hợp.

Cách tạo object của class `PartitionedMatrixView`:
Các constructor:
```cpp
  PartitionedMatrixView(const LinearSolver::Options & options, const BlockSparseMatrix & matrix)
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1212_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
