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

- Hàm: `ReorderSchurComplementColumnsUsingEigen(LinearSolverOrderingType ordering_type, const int size_of_first_elimination_group, const ProblemImpl::ParameterMap &, Program * program)`, trả về `void`
- Loại: hàm tự do (không thuộc class)
- Namespace: `ceres::internal`
- Vị trí: `internal/ceres/reorder_program.cc`, dòng 382–442

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
382 | static void ReorderSchurComplementColumnsUsingEigen(
383 |     LinearSolverOrderingType ordering_type,
384 |     const int size_of_first_elimination_group,
385 |     const ProblemImpl::ParameterMap& /*parameter_map*/,
386 |     Program* program) {
387 | #if defined(CERES_USE_EIGEN_SPARSE)
388 |   std::unique_ptr<TripletSparseMatrix> tsm_block_jacobian_transpose(
389 |       program->CreateJacobianBlockSparsityTranspose());
390 |   using SparseMatrix = Eigen::SparseMatrix<int>;
391 |   const SparseMatrix block_jacobian =
392 |       CreateBlockJacobian(*tsm_block_jacobian_transpose);
393 |   const int num_rows = block_jacobian.rows();
394 |   const int num_cols = block_jacobian.cols();
395 | 
396 |   // Vertically partition the jacobian in parameter blocks of type E
397 |   // and F.
398 |   const SparseMatrix E =
399 |       block_jacobian.block(0, 0, num_rows, size_of_first_elimination_group);
400 |   const SparseMatrix F =
401 |       block_jacobian.block(0,
402 |                            size_of_first_elimination_group,
403 |                            num_rows,
404 |                            num_cols - size_of_first_elimination_group);
405 | 
406 |   // Block sparsity pattern of the schur complement.
407 |   const SparseMatrix block_schur_complement =
408 |       F.transpose() * F - F.transpose() * E * E.transpose() * F;
409 | 
410 |   Eigen::PermutationMatrix<Eigen::Dynamic, Eigen::Dynamic, int> perm;
411 |   if (ordering_type == ceres::AMD) {
412 |     Eigen::AMDOrdering<int> amd_ordering;
413 |     amd_ordering(block_schur_complement, perm);
414 |   } else {
415 | #ifndef CERES_NO_EIGEN_METIS
416 |     Eigen::MetisOrdering<int> metis_ordering;
417 |     metis_ordering(block_schur_complement, perm);
418 | #else
419 |     perm.setIdentity(block_schur_complement.rows());
420 | #endif
421 |   }
422 | 
423 |   const std::vector<ParameterBlock*>& parameter_blocks =
424 |       program->parameter_blocks();
425 |   std::vector<ParameterBlock*> ordering(num_cols);
426 | 
427 |   // The ordering of the first size_of_first_elimination_group does
428 |   // not matter, so we preserve the existing ordering.
429 |   for (int i = 0; i < size_of_first_elimination_group; ++i) {
430 |     ordering[i] = parameter_blocks[i];
431 |   }
432 | 
433 |   // For the rest of the blocks, use the ordering computed using AMD.
434 |   for (int i = 0; i < block_schur_complement.cols(); ++i) {
435 |     ordering[size_of_first_elimination_group + i] =
436 |         parameter_blocks[size_of_first_elimination_group + perm.indices()[i]];
437 |   }
438 | 
439 |   swap(*program->mutable_parameter_blocks(), ordering);
440 |   program->SetParameterOffsetsAndIndex();
441 | #endif
442 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 3

START → 1
1   operator* (ImplicitCastExpr, FunctionToPointerDecay, typename add_lvalue_reference<element_type>::type (*)(void) const noexcept(noexcept(*std::declval<pointer>())))
    CreateBlockJacobian(* tsm_block_jacobian_transpose)
    const int num_rows = block_jacobian.rows()
    const int num_cols = block_jacobian.cols()
    block_jacobian.block(0, 0, num_rows, size_of_first_elimination_group)
    block_jacobian.block(0, size_of_first_elimination_group, num_rows, num_cols - size_of_first_elimination_group)
    F.transpose() * F - F.transpose() * E * E.transpose() * F      → 2
2   if (ordering_type == ceres::AMD)                               đúng → 3   sai → 13
3   amd_ordering(block_schur_complement, perm)                     → 4
4   const std::vector<ParameterBlock *> &parameter_blocks = program->parameter_blocks()
    int i = 0                                                      → 5
5   vòng for, điều kiện: i < size_of_first_elimination_group       đúng → 6   sai → 8
6   ordering[i] = parameter_blocks[i]                              → 7
7   ++i                                                            → 5
8   int i = 0                                                      → 9
9   vòng for, điều kiện: i < block_schur_complement.cols()         đúng → 10   sai → 12
10  ordering[size_of_first_elimination_group + i] = parameter_blocks[size_of_first_elimination_group + perm.indices()[i]]   → 11
11  ++i                                                            → 9
12  swap (ImplicitCastExpr, FunctionToPointerDecay, void (*)(vector<ParameterBlock *, allocator<ParameterBlock *> > &, vector<ParameterBlock *, allocator<ParameterBlock *> > &) noexcept(noexcept(__x.swap(__y))))(*program->mutable_parameter_blocks(), ordering)
    program->SetParameterOffsetsAndIndex()                         → END
13  perm.setIdentity(block_schur_complement.rows())                → 4
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
#include "ceres/reorder_program.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"
#include "ceres/program.h"
#include "ceres/triplet_sparse_matrix.h"
#include "ceres/reorder_program.cc"
```

- Hàm này chỉ dùng được bên trong file `internal/ceres/reorder_program.cc` (khai báo `static` hoặc trong namespace không tên). Để gọi được, thêm `#include "ceres/reorder_program.cc"` vào file test.

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1453_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
