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

- Hàm: `Compute()`, trả về `void`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::InnerProductComputer`
- Vị trí: `internal/ceres/inner_product_computer.cc`, dòng 286–334

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
286 | void InnerProductComputer::Compute() {
287 |   const double* m_values = m_.values();
288 |   const CompressedRowBlockStructure* bs = m_.block_structure();
289 | 
290 |   const CompressedRowSparseMatrix::StorageType storage_type =
291 |       result_->storage_type();
292 |   result_->SetZero();
293 |   double* values = result_->mutable_values();
294 |   const int* rows = result_->rows();
295 |   int cursor = 0;
296 | 
297 |   // Iterate row blocks.
298 |   for (int r = start_row_block_; r < end_row_block_; ++r) {
299 |     const CompressedRow& m_row = bs->rows[r];
300 |     for (int c1 = 0; c1 < m_row.cells.size(); ++c1) {
301 |       const Cell& cell1 = m_row.cells[c1];
302 |       const int c1_size = bs->cols[cell1.block_id].size;
303 |       const int row_nnz = rows[bs->cols[cell1.block_id].position + 1] -
304 |                           rows[bs->cols[cell1.block_id].position];
305 | 
306 |       int c2_begin, c2_end;
307 |       if (storage_type ==
308 |           CompressedRowSparseMatrix::StorageType::LOWER_TRIANGULAR) {
309 |         c2_begin = 0;
310 |         c2_end = c1 + 1;
311 |       } else {
312 |         c2_begin = c1;
313 |         c2_end = m_row.cells.size();
314 |       }
315 | 
316 |       for (int c2 = c2_begin; c2 < c2_end; ++c2, ++cursor) {
317 |         const Cell& cell2 = m_row.cells[c2];
318 |         const int c2_size = bs->cols[cell2.block_id].size;
319 |         // clang-format off
320 |         MatrixTransposeMatrixMultiply<Eigen::Dynamic, Eigen::Dynamic,
321 |                                       Eigen::Dynamic, Eigen::Dynamic, 1>(
322 |                                           m_values + cell1.position,
323 |                                           m_row.block.size, c1_size,
324 |                                           m_values + cell2.position,
325 |                                           m_row.block.size, c2_size,
326 |                                           values + result_offsets_[cursor],
327 |                                           0, 0, c1_size, row_nnz);
328 |         // clang-format on
329 |       }
330 |     }
331 |   }
332 | 
333 |   CHECK_EQ(cursor, result_offsets_.size());
334 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 4 (và 1 lệnh CHECK)

START → 1
1   const double *m_values = m_.values()
    const CompressedRowBlockStructure *bs = m_.block_structure()
    const CompressedRowSparseMatrix::StorageType storage_type = result_->storage_type()
    result_->SetZero()
    double *values = result_->mutable_values()
    const int *rows = result_->rows()
    int cursor = 0
    int r = start_row_block_                                       → 2
2   vòng for, điều kiện: r < end_row_block_                        đúng → 3   sai → 15
3   const CompressedRow &m_row = bs->rows[r]
    int c1 = 0                                                     → 4
4   vòng for, điều kiện: c1 < m_row.cells.size()                   đúng → 5   sai → 14
5   const Cell &cell1 = m_row.cells[c1]
    const int c1_size = bs->cols[cell1.block_id].size
    const int row_nnz = rows[bs->cols[cell1.block_id].position + 1] - rows[bs->cols[cell1.block_id].position]
    int c2_begin
    int c2_end                                                     → 6
6   if (storage_type == CompressedRowSparseMatrix::StorageType::LOWER_TRIANGULAR)   đúng → 7   sai → 13
7   c2_begin = 0
    c2_end = c1 + 1                                                → 8
8   int c2 = c2_begin                                              → 9
9   vòng for, điều kiện: c2 < c2_end                               đúng → 10   sai → 12
10  const Cell &cell2 = m_row.cells[c2]
    const int c2_size = bs->cols[cell2.block_id].size
    MatrixTransposeMatrixMultiply<Eigen::Dynamic, Eigen::Dynamic, Eigen::Dynamic, Eigen::Dynamic, 1>(m_values + cell1.position, m_row.block.size, c1_size, m_values + cell2.position, m_row.block.size, c2_size, values + result_offsets_[cursor], 0, 0, c1_size, row_nnz)   → 11
11  ++c2                                                           → 9
12  ++c1                                                           → 4
13  c2_begin = c1
    c2_end = m_row.cells.size()                                    → 8
14  ++r                                                            → 2
15  CHECK_EQ(cursor, result_offsets_.size())                       đúng → END   sai → DỪNG
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
#include "ceres/inner_product_computer.h"
#include "ceres/small_blas.h"
```

- Đây là method của class `ceres::internal::InnerProductComputer`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `InnerProductComputer`:
Các constructor:
```cpp
  InnerProductComputer(const BlockSparseMatrix & m, const int start_row_block, const int end_row_block)   // private
  InnerProductComputer(const BlockSparseMatrix & m, int start_row_block, int end_row_block)   // private
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1202_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
