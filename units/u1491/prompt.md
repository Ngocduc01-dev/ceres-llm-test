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

- Hàm: `Evaluate(const Problem::EvaluateOptions & evaluate_options, double * cost, std::vector<double> * residuals, std::vector<double> * gradient, CRSMatrix * jacobian)`, trả về `bool`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::ProblemImpl`
- Vị trí: `internal/ceres/problem_impl.cc`, dòng 585–746

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
585 | bool ProblemImpl::Evaluate(const Problem::EvaluateOptions& evaluate_options,
586 |                            double* cost,
587 |                            std::vector<double>* residuals,
588 |                            std::vector<double>* gradient,
589 |                            CRSMatrix* jacobian) {
590 |   if (cost == nullptr && residuals == nullptr && gradient == nullptr &&
591 |       jacobian == nullptr) {
592 |     return true;
593 |   }
594 | 
595 |   // If the user supplied residual blocks, then use them, otherwise
596 |   // take the residual blocks from the underlying program.
597 |   Program program;
598 |   *program.mutable_residual_blocks() =
599 |       ((evaluate_options.residual_blocks.size() > 0)
600 |            ? evaluate_options.residual_blocks
601 |            : program_->residual_blocks());
602 | 
603 |   const std::vector<double*>& parameter_block_ptrs =
604 |       evaluate_options.parameter_blocks;
605 | 
606 |   std::vector<ParameterBlock*> variable_parameter_blocks;
607 |   std::vector<ParameterBlock*>& parameter_blocks =
608 |       *program.mutable_parameter_blocks();
609 | 
610 |   if (parameter_block_ptrs.size() == 0) {
611 |     // The user did not provide any parameter blocks, so default to
612 |     // using all the parameter blocks in the order that they are in
613 |     // the underlying program object.
614 |     parameter_blocks = program_->parameter_blocks();
615 |   } else {
616 |     // The user supplied a vector of parameter blocks. Using this list
617 |     // requires a number of steps.
618 | 
619 |     // 1. Convert double* into ParameterBlock*
620 |     parameter_blocks.resize(parameter_block_ptrs.size());
621 |     for (int i = 0; i < parameter_block_ptrs.size(); ++i) {
622 |       parameter_blocks[i] = FindWithDefault(
623 |           parameter_block_map_, parameter_block_ptrs[i], nullptr);
624 |       if (parameter_blocks[i] == nullptr) {
625 |         LOG(FATAL) << "No known parameter block for "
626 |                    << "Problem::Evaluate::Options.parameter_blocks[" << i << "]"
627 |                    << " = " << parameter_block_ptrs[i];
628 |       }
629 |     }
630 | 
631 |     // 2. The user may have only supplied a subset of parameter
632 |     // blocks, so identify the ones that are not supplied by the user
633 |     // and are NOT constant. These parameter blocks are stored in
634 |     // variable_parameter_blocks.
635 |     //
636 |     // To ensure that the parameter blocks are not included in the
637 |     // columns of the jacobian, we need to make sure that they are
638 |     // constant during evaluation and then make them variable again
639 |     // after we are done.
640 |     std::vector<ParameterBlock*> all_parameter_blocks(
641 |         program_->parameter_blocks());
642 |     std::vector<ParameterBlock*> included_parameter_blocks(
643 |         program.parameter_blocks());
644 | 
645 |     std::vector<ParameterBlock*> excluded_parameter_blocks;
646 |     sort(all_parameter_blocks.begin(), all_parameter_blocks.end());
647 |     sort(included_parameter_blocks.begin(), included_parameter_blocks.end());
648 |     set_difference(all_parameter_blocks.begin(),
649 |                    all_parameter_blocks.end(),
650 |                    included_parameter_blocks.begin(),
651 |                    included_parameter_blocks.end(),
652 |                    back_inserter(excluded_parameter_blocks));
653 | 
654 |     variable_parameter_blocks.reserve(excluded_parameter_blocks.size());
655 |     for (auto* parameter_block : excluded_parameter_blocks) {
656 |       if (!parameter_block->IsConstant()) {
657 |         variable_parameter_blocks.push_back(parameter_block);
658 |         parameter_block->SetConstant();
659 |       }
660 |     }
661 |   }
662 | 
663 |   // Setup the Parameter indices and offsets before an evaluator can
664 |   // be constructed and used.
665 |   program.SetParameterOffsetsAndIndex();
666 | 
667 |   Evaluator::Options evaluator_options;
668 | 
669 |   // Even though using SPARSE_NORMAL_CHOLESKY requires SuiteSparse or
670 |   // CXSparse, here it just being used for telling the evaluator to
671 |   // use a SparseRowCompressedMatrix for the jacobian. This is because
672 |   // the Evaluator decides the storage for the Jacobian based on the
673 |   // type of linear solver being used.
674 |   evaluator_options.linear_solver_type = SPARSE_NORMAL_CHOLESKY;
675 |   evaluator_options.num_threads = evaluate_options.num_threads;
676 | 
677 |   // The main thread also does work so we only need to launch num_threads - 1.
678 |   context_impl_->EnsureMinimumThreads(evaluator_options.num_threads - 1);
679 |   evaluator_options.context = context_impl_;
680 |   evaluator_options.evaluation_callback =
681 |       program_->mutable_evaluation_callback();
682 |   std::unique_ptr<Evaluator> evaluator(
683 |       new ProgramEvaluator<ScratchEvaluatePreparer,
684 |                            CompressedRowJacobianWriter>(evaluator_options,
685 |                                                         &program));
686 | 
687 |   if (residuals != nullptr) {
688 |     residuals->resize(evaluator->NumResiduals());
689 |   }
690 | 
691 |   if (gradient != nullptr) {
692 |     gradient->resize(evaluator->NumEffectiveParameters());
693 |   }
694 | 
695 |   std::unique_ptr<CompressedRowSparseMatrix> tmp_jacobian;
696 |   if (jacobian != nullptr) {
697 |     tmp_jacobian.reset(down_cast<CompressedRowSparseMatrix*>(
698 |         evaluator->CreateJacobian().release()));
699 |   }
700 | 
701 |   // Point the state pointers to the user state pointers. This is
702 |   // needed so that we can extract a parameter vector which is then
703 |   // passed to Evaluator::Evaluate.
704 |   program.SetParameterBlockStatePtrsToUserStatePtrs();
705 | 
706 |   // Copy the value of the parameter blocks into a vector, since the
707 |   // Evaluate::Evaluate method needs its input as such. The previous
708 |   // call to SetParameterBlockStatePtrsToUserStatePtrs ensures that
709 |   // these values are the ones corresponding to the actual state of
710 |   // the parameter blocks, rather than the temporary state pointer
711 |   // used for evaluation.
712 |   Vector parameters(program.NumParameters());
713 |   program.ParameterBlocksToStateVector(parameters.data());
714 | 
715 |   double tmp_cost = 0;
716 | 
717 |   Evaluator::EvaluateOptions evaluator_evaluate_options;
718 |   evaluator_evaluate_options.apply_loss_function =
719 |       evaluate_options.apply_loss_function;
720 |   bool status =
721 |       evaluator->Evaluate(evaluator_evaluate_options,
722 |                           parameters.data(),
723 |                           &tmp_cost,
724 |                           residuals != nullptr ? &(*residuals)[0] : nullptr,
725 |                           gradient != nullptr ? &(*gradient)[0] : nullptr,
726 |                           tmp_jacobian.get());
727 | 
728 |   // Make the parameter blocks that were temporarily marked constant,
729 |   // variable again.
730 |   for (auto* parameter_block : variable_parameter_blocks) {
731 |     parameter_block->SetVarying();
732 |   }
733 | 
734 |   if (status) {
735 |     if (cost != nullptr) {
736 |       *cost = tmp_cost;
737 |     }
738 |     if (jacobian != nullptr) {
739 |       tmp_jacobian->ToCRSMatrix(jacobian);
740 |     }
741 |   }
742 | 
743 |   program_->SetParameterBlockStatePtrsToUserStatePtrs();
744 |   program_->SetParameterOffsetsAndIndex();
745 |   return status;
746 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 15 (và 1 lệnh CHECK)

START → 1
1   if (cost == nullptr && residuals == nullptr && gradient == nullptr && jacobian == nullptr)   đúng → 2   sai → 3
2   return true                                                    → END
3   (evaluate_options.residual_blocks.size() > 0) ? ... : ...      đúng → 4   sai → 40
4   *program.mutable_residual_blocks() = ((evaluate_options.residual_blocks.size() > 0) ? evaluate_options.residual_blocks : program_->residual_blocks())
    const std::vector<double *> &parameter_block_ptrs = evaluate_options.parameter_blocks
    std::vector<ParameterBlock *> &parameter_blocks = *program.mutable_parameter_blocks()   → 5
5   if (parameter_block_ptrs.size() == 0)                          đúng → 6   sai → 29
6   parameter_blocks = program_->parameter_blocks()                → 7
7   program.SetParameterOffsetsAndIndex()
    evaluator_options.linear_solver_type = SPARSE_NORMAL_CHOLESKY
    evaluator_options.num_threads = evaluate_options.num_threads
    context_impl_->EnsureMinimumThreads(evaluator_options.num_threads - 1)
    evaluator_options.context = context_impl_
    evaluator_options.evaluation_callback = program_->mutable_evaluation_callback()
    CFGNewAllocator(ProgramEvaluator<ScratchEvaluatePreparer, CompressedRowJacobianWriter> *)
    new ProgramEvaluator<ScratchEvaluatePreparer, CompressedRowJacobianWriter>(evaluator_options, &program)   → 8
8   if (residuals != nullptr)                                      đúng → 9   sai → 10
9   residuals->resize(evaluator->NumResiduals())                   → 10
10  if (gradient != nullptr)                                       đúng → 11   sai → 12
11  gradient->resize(evaluator->NumEffectiveParameters())          → 12
12  if (jacobian != nullptr)                                       đúng → 13   sai → 14
13  tmp_jacobian.reset(down_cast<CompressedRowSparseMatrix *>(evaluator->CreateJacobian().release()))   → 14
14  program.SetParameterBlockStatePtrsToUserStatePtrs()
    program.NumParameters()
    program.ParameterBlocksToStateVector(parameters.data())
    double tmp_cost = 0
    evaluator_evaluate_options.apply_loss_function = evaluate_options.apply_loss_function   → 15
15  residuals != nullptr ? ... : ...                               đúng → 16   sai → 17
16  operator[]                                                     → 17
17  gradient != nullptr ? ... : ...                                đúng → 18   sai → 19
18  operator[]                                                     → 19
19  bool status = evaluator->Evaluate(evaluator_evaluate_options, parameters.data(), &tmp_cost, residuals != nullptr ? &(*residuals)[0] : nullptr, gradient != nullptr ? &(*gradient)[0] : nullptr, tmp_jacobian.get())   → 20
20  for (auto *parameter_block : variable_parameter_blocks)        đúng → 21   sai → 23
21  auto *parameter_block
    parameter_block->SetVarying()                                  → 22
22  ++ (bước tiếp của vòng for)                                    → 20
23  if (status)                                                    đúng → 24   sai → 28
24  if (cost != nullptr)                                           đúng → 25   sai → 26
25  *cost = tmp_cost                                               → 26
26  if (jacobian != nullptr)                                       đúng → 27   sai → 28
27  tmp_jacobian->ToCRSMatrix(jacobian)                            → 28
28  program_->SetParameterBlockStatePtrsToUserStatePtrs()
    program_->SetParameterOffsetsAndIndex()
    return status                                                  → END
29  parameter_blocks.resize(parameter_block_ptrs.size())
    int i = 0                                                      → 30
30  vòng for, điều kiện: i < parameter_block_ptrs.size()           đúng → 31   sai → 34
31  parameter_blocks[i] = FindWithDefault(parameter_block_map_, parameter_block_ptrs[i], nullptr)   → 32
32  LOG(FATAL)                                                     đúng → 33   sai → DỪNG
33  ++i                                                            → 30
34  program_->parameter_blocks()
    program.parameter_blocks()
    variable_parameter_blocks.reserve(excluded_parameter_blocks.size())   → 35
35  for (auto *parameter_block : excluded_parameter_blocks)        đúng → 36   sai → 7
36  auto *parameter_block                                          → 37
37  if (!parameter_block->IsConstant())                            đúng → 38   sai → 39
38  variable_parameter_blocks.push_back(parameter_block)
    parameter_block->SetConstant()                                 → 39
39  ++ (bước tiếp của vòng for)                                    → 35
40  operator->                                                     → 4
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
#include "ceres/crs_matrix.h"
#include "ceres/problem.h"
#include "ceres/casts.h"
#include "ceres/compressed_row_jacobian_writer.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/evaluator.h"
#include "ceres/map_util.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"
#include "ceres/program.h"
#include "ceres/program_evaluator.h"
#include "ceres/scratch_evaluate_preparer.h"
```

- Đây là method của class `ceres::internal::ProblemImpl`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `ProblemImpl`:
Các constructor:
```cpp
  ProblemImpl()
  ProblemImpl(const Problem::Options & options)
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1491_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
