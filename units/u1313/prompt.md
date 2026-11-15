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

- Hàm: `ChunkDiagonalBlockAndGradient(const Chunk & chunk, const BlockSparseMatrixData & A, const double * b, int row_block_counter, typename EigenTypes<kEBlockSize, kEBlockSize>::Matrix * ete, double * g, double * buffer, BlockRandomAccessMatrix * lhs)`, trả về `void`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::SchurEliminator` (class template)
- Vị trí: `internal/ceres/schur_eliminator_impl.h`, dòng 441–505

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
441 | template <int kRowBlockSize, int kEBlockSize, int kFBlockSize>
442 | void SchurEliminator<kRowBlockSize, kEBlockSize, kFBlockSize>::
443 |     ChunkDiagonalBlockAndGradient(
444 |         const Chunk& chunk,
445 |         const BlockSparseMatrixData& A,
446 |         const double* b,
447 |         int row_block_counter,
448 |         typename EigenTypes<kEBlockSize, kEBlockSize>::Matrix* ete,
449 |         double* g,
450 |         double* buffer,
451 |         BlockRandomAccessMatrix* lhs) {
452 |   const CompressedRowBlockStructure* bs = A.block_structure();
453 |   const double* values = A.values();
454 | 
455 |   int b_pos = bs->rows[row_block_counter].block.position;
456 |   const int e_block_size = ete->rows();
457 | 
458 |   // Iterate over the rows in this chunk, for each row, compute the
459 |   // contribution of its F blocks to the Schur complement, the
460 |   // contribution of its E block to the matrix EE' (ete), and the
461 |   // corresponding block in the gradient vector.
462 |   for (int j = 0; j < chunk.size; ++j) {
463 |     const CompressedRow& row = bs->rows[row_block_counter + j];
464 | 
465 |     if (row.cells.size() > 1) {
466 |       EBlockRowOuterProduct(A, row_block_counter + j, lhs);
467 |     }
468 | 
469 |     // Extract the e_block, ETE += E_i' E_i
470 |     const Cell& e_cell = row.cells.front();
471 |     // clang-format off
472 |     MatrixTransposeMatrixMultiply
473 |         <kRowBlockSize, kEBlockSize, kRowBlockSize, kEBlockSize, 1>(
474 |             values + e_cell.position, row.block.size, e_block_size,
475 |             values + e_cell.position, row.block.size, e_block_size,
476 |             ete->data(), 0, 0, e_block_size, e_block_size);
477 |     // clang-format on
478 | 
479 |     if (b) {
480 |       // g += E_i' b_i
481 |       // clang-format off
482 |       MatrixTransposeVectorMultiply<kRowBlockSize, kEBlockSize, 1>(
483 |           values + e_cell.position, row.block.size, e_block_size,
484 |           b + b_pos,
485 |           g);
486 |       // clang-format on
487 |     }
488 | 
489 |     // buffer = E'F. This computation is done by iterating over the
490 |     // f_blocks for each row in the chunk.
491 |     for (int c = 1; c < row.cells.size(); ++c) {
492 |       const int f_block_id = row.cells[c].block_id;
493 |       const int f_block_size = bs->cols[f_block_id].size;
494 |       double* buffer_ptr = buffer + FindOrDie(chunk.buffer_layout, f_block_id);
495 |       // clang-format off
496 |       MatrixTransposeMatrixMultiply
497 |           <kRowBlockSize, kEBlockSize, kRowBlockSize, kFBlockSize, 1>(
498 |           values + e_cell.position, row.block.size, e_block_size,
499 |           values + row.cells[c].position, row.block.size, f_block_size,
500 |           buffer_ptr, 0, 0, e_block_size, f_block_size);
501 |       // clang-format on
502 |     }
503 |     b_pos += row.block.size;
504 |   }
505 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Ghi chú: đây là template – một số kiểu dữ liệu còn để trống, chỉ được điền khi dùng. CFG dưới đây dựng cho trường hợp SchurEliminator<>.

Số điểm rẽ nhánh: 4

START → 1
1   const CompressedRowBlockStructure *bs = A.block_structure()
    const double *values = A.values()
    int b_pos = bs->rows[row_block_counter].block.position
    const int e_block_size = ete->rows()
    int j = 0                                                      → 2
2   vòng for, điều kiện: j < chunk.size                            đúng → 3   sai → END
3   const CompressedRow &row = bs->rows[row_block_counter + j]     → 4
4   if (row.cells.size() > 1)                                      đúng → 5   sai → 6
5   EBlockRowOuterProduct(A, row_block_counter + j, lhs)           → 6
6   const Cell &e_cell = row.cells.front()
    MatrixTransposeMatrixMultiply<-1, -1, -1, -1, 1>(values + e_cell.position, row.block.size, e_block_size, values + e_cell.position, row.block.size, e_block_size, ete->data(), 0, 0, e_block_size, e_block_size)   → 7
7   if (b)                                                         đúng → 8   sai → 9
8   MatrixTransposeVectorMultiply<-1, -1, 1>(values + e_cell.position, row.block.size, e_block_size, b + b_pos, g)   → 9
9   int c = 1                                                      → 10
10  vòng for, điều kiện: c < row.cells.size()                      đúng → 11   sai → 13
11  const int f_block_id = row.cells[c].block_id
    const int f_block_size = bs->cols[f_block_id].size
    double *buffer_ptr = buffer + FindOrDie(chunk.buffer_layout, f_block_id)
    MatrixTransposeMatrixMultiply<-1, -1, -1, -1, 1>(values + e_cell.position, row.block.size, e_block_size, values + row.cells[c].position, row.block.size, f_block_size, buffer_ptr, 0, 0, e_block_size, f_block_size)   → 12
12  ++c                                                            → 10
13  b_pos += row.block.size                                        → 14
14  ++j                                                            → 2
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
#include "ceres/block_random_access_matrix.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/schur_eliminator.h"
#include "ceres/schur_eliminator_impl.h"
```

- Method này là `private` (bên ngoài class không gọi được). Thêm 2 dòng `#define private public` và `#define protected public` **sau** `#include "gtest/gtest.h"` và **trước** các `#include` của Ceres.
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1313_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
