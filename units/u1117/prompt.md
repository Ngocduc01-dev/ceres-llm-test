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

- Hàm: `BackSubstitute(const BlockSparseMatrixData & A, const double * b, const double * D, const double * z, double * y)`, trả về `void`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::SchurEliminator` (class template)
- Vị trí: `internal/ceres/schur_eliminator_impl.h`, dòng 306–373

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
306 | template <int kRowBlockSize, int kEBlockSize, int kFBlockSize>
307 | void SchurEliminator<kRowBlockSize, kEBlockSize, kFBlockSize>::BackSubstitute(
308 |     const BlockSparseMatrixData& A,
309 |     const double* b,
310 |     const double* D,
311 |     const double* z,
312 |     double* y) {
313 |   const CompressedRowBlockStructure* bs = A.block_structure();
314 |   const double* values = A.values();
315 | 
316 |   ParallelFor(context_, 0, int(chunks_.size()), num_threads_, [&](int i) {
317 |     const Chunk& chunk = chunks_[i];
318 |     const int e_block_id = bs->rows[chunk.start].cells.front().block_id;
319 |     const int e_block_size = bs->cols[e_block_id].size;
320 | 
321 |     double* y_ptr = y + bs->cols[e_block_id].position;
322 |     typename EigenTypes<kEBlockSize>::VectorRef y_block(y_ptr, e_block_size);
323 | 
324 |     typename EigenTypes<kEBlockSize, kEBlockSize>::Matrix ete(e_block_size,
325 |                                                               e_block_size);
326 |     if (D != nullptr) {
327 |       const typename EigenTypes<kEBlockSize>::ConstVectorRef diag(
328 |           D + bs->cols[e_block_id].position, e_block_size);
329 |       ete = diag.array().square().matrix().asDiagonal();
330 |     } else {
331 |       ete.setZero();
332 |     }
333 | 
334 |     for (int j = 0; j < chunk.size; ++j) {
335 |       const CompressedRow& row = bs->rows[chunk.start + j];
336 |       const Cell& e_cell = row.cells.front();
337 |       DCHECK_EQ(e_block_id, e_cell.block_id);
338 | 
339 |       FixedArray<double, 8> sj(row.block.size);
340 | 
341 |       typename EigenTypes<kRowBlockSize>::VectorRef(sj.data(), row.block.size) =
342 |           typename EigenTypes<kRowBlockSize>::ConstVectorRef(
343 |               b + bs->rows[chunk.start + j].block.position, row.block.size);
344 | 
345 |       for (int c = 1; c < row.cells.size(); ++c) {
346 |         const int f_block_id = row.cells[c].block_id;
347 |         const int f_block_size = bs->cols[f_block_id].size;
348 |         const int r_block = f_block_id - num_eliminate_blocks_;
349 | 
350 |         // clang-format off
351 |         MatrixVectorMultiply<kRowBlockSize, kFBlockSize, -1>(
352 |             values + row.cells[c].position, row.block.size, f_block_size,
353 |             z + lhs_row_layout_[r_block],
354 |             sj.data());
355 |       }
356 | 
357 |       MatrixTransposeVectorMultiply<kRowBlockSize, kEBlockSize, 1>(
358 |           values + e_cell.position, row.block.size, e_block_size,
359 |           sj.data(),
360 |           y_ptr);
361 | 
362 |       MatrixTransposeMatrixMultiply
363 |           <kRowBlockSize, kEBlockSize, kRowBlockSize, kEBlockSize, 1>(
364 |           values + e_cell.position, row.block.size, e_block_size,
365 |           values + e_cell.position, row.block.size, e_block_size,
366 |           ete.data(), 0, 0, e_block_size, e_block_size);
367 |       // clang-format on
368 |     }
369 | 
370 |     y_block =
371 |         InvertPSDMatrix<kEBlockSize>(assume_full_rank_ete_, ete) * y_block;
372 |   });
373 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Ghi chú: đây là template – một số kiểu dữ liệu còn để trống, chỉ được điền khi dùng. CFG dưới đây dựng cho trường hợp SchurEliminator<>.

Số điểm rẽ nhánh: 0

START → 1
1   const CompressedRowBlockStructure *bs = A.block_structure()
    const double *values = A.values()
    ParallelFor (ImplicitCastExpr, FunctionToPointerDecay, void (*)(ContextImpl *, int, int, int, class (lambda at /work/ceres-solver/internal/ceres/schur_eliminator_impl.h:316:63) &&, int))(context_, 0, int(chunks_.size()), num_threads_, [&](int i) {)   → END
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
#include "ceres/internal/eigen.h"
#include "ceres/internal/fixed_array.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/schur_eliminator.h"
#include "ceres/schur_eliminator_impl.h"
```

- Đây là method của class `ceres::internal::SchurEliminator`: tạo một object của class rồi gọi method trên object đó.
- Đây là template (khuôn mẫu): khi tạo object hoặc gọi hàm phải chọn kiểu cụ thể phù hợp.

Cách tạo object của class `SchurEliminator`:
Các constructor:
```cpp
  SchurEliminator(const LinearSolver::Options & options)
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1117_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
