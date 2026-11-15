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

- Hàm: `ReorderProgramForSchurTypeLinearSolver(const LinearSolverType linear_solver_type, const SparseLinearAlgebraLibraryType sparse_linear_algebra_library_type, const LinearSolverOrderingType linear_solver_ordering_type, const ProblemImpl::ParameterMap & parameter_map, ParameterBlockOrdering * parameter_block_ordering, Program * program, std::string * error)`, trả về `bool`
- Loại: hàm tự do (không thuộc class)
- Namespace: `ceres::internal`
- Vị trí: `internal/ceres/reorder_program.cc`, dòng 444–538

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
444 | bool ReorderProgramForSchurTypeLinearSolver(
445 |     const LinearSolverType linear_solver_type,
446 |     const SparseLinearAlgebraLibraryType sparse_linear_algebra_library_type,
447 |     const LinearSolverOrderingType linear_solver_ordering_type,
448 |     const ProblemImpl::ParameterMap& parameter_map,
449 |     ParameterBlockOrdering* parameter_block_ordering,
450 |     Program* program,
451 |     std::string* error) {
452 |   if (parameter_block_ordering->NumElements() !=
453 |       program->NumParameterBlocks()) {
454 |     *error = StringPrintf(
455 |         "The program has %d parameter blocks, but the parameter block "
456 |         "ordering has %d parameter blocks.",
457 |         program->NumParameterBlocks(),
458 |         parameter_block_ordering->NumElements());
459 |     return false;
460 |   }
461 | 
462 |   if (parameter_block_ordering->NumGroups() == 1) {
463 |     // If the user supplied an parameter_block_ordering with just one
464 |     // group, it is equivalent to the user supplying nullptr as an
465 |     // parameter_block_ordering. Ceres is completely free to choose the
466 |     // parameter block ordering as it sees fit. For Schur type solvers,
467 |     // this means that the user wishes for Ceres to identify the
468 |     // e_blocks, which we do by computing a maximal independent set.
469 |     std::vector<ParameterBlock*> schur_ordering;
470 |     const int size_of_first_elimination_group =
471 |         ComputeStableSchurOrdering(*program, &schur_ordering);
472 | 
473 |     CHECK_EQ(schur_ordering.size(), program->NumParameterBlocks())
474 |         << "Congratulations, you found a Ceres bug! Please report this error "
475 |         << "to the developers.";
476 | 
477 |     // Update the parameter_block_ordering object.
478 |     for (int i = 0; i < schur_ordering.size(); ++i) {
479 |       double* parameter_block = schur_ordering[i]->mutable_user_state();
480 |       const int group_id = (i < size_of_first_elimination_group) ? 0 : 1;
481 |       parameter_block_ordering->AddElementToGroup(parameter_block, group_id);
482 |     }
483 | 
484 |     // We could call ApplyOrdering but this is cheaper and
485 |     // simpler.
486 |     swap(*program->mutable_parameter_blocks(), schur_ordering);
487 |   } else {
488 |     // The user provided an ordering with more than one elimination
489 |     // group.
490 | 
491 |     // Verify that the first elimination group is an independent set.
492 | 
493 |     // TODO(sameeragarwal): Investigate if this should be a set or an
494 |     // unordered_set.
495 |     const std::set<double*>& first_elimination_group =
496 |         parameter_block_ordering->group_to_elements().begin()->second;
497 |     if (!program->IsParameterBlockSetIndependent(first_elimination_group)) {
498 |       *error = StringPrintf(
499 |           "The first elimination group in the parameter block "
500 |           "ordering of size %zd is not an independent set",
501 |           first_elimination_group.size());
502 |       return false;
503 |     }
504 | 
505 |     if (!ApplyOrdering(
506 |             parameter_map, *parameter_block_ordering, program, error)) {
507 |       return false;
508 |     }
509 |   }
510 | 
511 |   program->SetParameterOffsetsAndIndex();
512 | 
513 |   const int size_of_first_elimination_group =
514 |       parameter_block_ordering->group_to_elements().begin()->second.size();
515 | 
516 |   if (linear_solver_type == SPARSE_SCHUR) {
517 |     if (sparse_linear_algebra_library_type == SUITE_SPARSE &&
518 |         linear_solver_ordering_type == ceres::AMD) {
519 |       // Preordering support for schur complement only works with AMD
520 |       // for now, since we are using CAMD.
521 |       //
522 |       // TODO(sameeragarwal): It maybe worth adding pre-ordering support for
523 |       // nested dissection too.
524 |       ReorderSchurComplementColumnsUsingSuiteSparse(*parameter_block_ordering,
525 |                                                     program);
526 |     } else if (sparse_linear_algebra_library_type == EIGEN_SPARSE) {
527 |       ReorderSchurComplementColumnsUsingEigen(linear_solver_ordering_type,
528 |                                               size_of_first_elimination_group,
529 |                                               parameter_map,
530 |                                               program);
531 |     }
532 |   }
533 | 
534 |   // Schur type solvers also require that their residual blocks be
535 |   // lexicographically ordered.
536 |   return LexicographicallyOrderResidualBlocks(
537 |       size_of_first_elimination_group, program, error);
538 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 9 (và 1 lệnh CHECK)

START → 1
1   if (parameter_block_ordering->NumElements() != program->NumParameterBlocks())   đúng → 2   sai → 3
2   operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = StringPrintf("The program has %d parameter blocks, but the parameter block ordering has %d parameter blocks.", program->NumParameterBlocks(), parameter_block_ordering->NumElements())
    return false                                                   → END
3   if (parameter_block_ordering->NumGroups() == 1)                đúng → 4   sai → 20
4   const int size_of_first_elimination_group = ComputeStableSchurOrdering(*program, &schur_ordering)   → 5
5   CHECK_EQ(schur_ordering.size(), program->NumParameterBlocks())   đúng → 6   sai → DỪNG
6   int i = 0                                                      → 7
7   vòng for, điều kiện: i < schur_ordering.size()                 đúng → 8   sai → 12
8   double *parameter_block = schur_ordering[i]->mutable_user_state()   → 9
9   (i < size_of_first_elimination_group) ? ... : ...              đúng → 10   sai → 10
10  const int group_id = (i < size_of_first_elimination_group) ? 0 : 1
    parameter_block_ordering->AddElementToGroup(parameter_block, group_id)   → 11
11  ++i                                                            → 7
12  swap (ImplicitCastExpr, FunctionToPointerDecay, void (*)(vector<ParameterBlock *, allocator<ParameterBlock *> > &, vector<ParameterBlock *, allocator<ParameterBlock *> > &) noexcept(noexcept(__x.swap(__y))))(*program->mutable_parameter_blocks(), schur_ordering)   → 13
13  program->SetParameterOffsetsAndIndex()
    const int size_of_first_elimination_group = parameter_block_ordering->group_to_elements().begin()->second.size()   → 14
14  if (linear_solver_type == SPARSE_SCHUR)                        đúng → 15   sai → 17
15  if (sparse_linear_algebra_library_type == SUITE_SPARSE && linear_solver_ordering_type == ceres::AMD)   đúng → 16   sai → 18
16  ReorderSchurComplementColumnsUsingSuiteSparse(*parameter_block_ordering, program)   → 17
17  return LexicographicallyOrderResidualBlocks(size_of_first_elimination_group, program, error)   → END
18  if (sparse_linear_algebra_library_type == EIGEN_SPARSE)        đúng → 19   sai → 17
19  ReorderSchurComplementColumnsUsingEigen(linear_solver_ordering_type, size_of_first_elimination_group, parameter_map, program)   → 17
20  const std::set<double *> &first_elimination_group = parameter_block_ordering->group_to_elements().begin()->second   → 21
21  if (!program->IsParameterBlockSetIndependent(first_elimination_group))   đúng → 22   sai → 23
22  operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = StringPrintf("The first elimination group in the parameter block ordering of size %zd is not an independent set", first_elimination_group.size())
    return false                                                   → END
23  if (!ApplyOrdering(parameter_map, *parameter_block_ordering, program, error))   đúng → 24   sai → 13
24  return false                                                   → END
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
#include "ceres/ordered_groups.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"
#include "ceres/program.h"
```

- Hàm gọi trực tiếp được.

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1470_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
