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

- Hàm: `LinearLeastSquaresProblem5()`, trả về `std::unique_ptr<LinearLeastSquaresProblem>`
- Loại: hàm tự do (không thuộc class)
- Namespace: `ceres::internal`
- Vị trí: `internal/ceres/linear_least_squares_problems.cc`, dòng 677–799

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
677 | std::unique_ptr<LinearLeastSquaresProblem> LinearLeastSquaresProblem5() {
678 |   int num_rows = 6;
679 |   int num_cols = 5;
680 | 
681 |   auto problem = std::make_unique<LinearLeastSquaresProblem>();
682 |   problem->b = std::make_unique<double[]>(num_rows);
683 |   problem->D = std::make_unique<double[]>(num_cols);
684 |   problem->num_eliminate_blocks = 2;
685 | 
686 |   // TODO: add x
687 |   problem->x = std::make_unique<double[]>(num_cols);
688 |   problem->x[0] = 0.2;
689 |   problem->x[1] = -1.4444;
690 |   problem->x[2] = 0.9777;
691 |   problem->x[3] = -0.3888;
692 |   problem->x[4] = 0.1;
693 | 
694 |   auto* bs = new CompressedRowBlockStructure;
695 |   auto values = std::make_unique<double[]>(num_rows * num_cols);
696 | 
697 |   for (int c = 0; c < num_cols; ++c) {
698 |     bs->cols.emplace_back();
699 |     bs->cols.back().size = 1;
700 |     bs->cols.back().position = c;
701 |   }
702 | 
703 |   int nnz = 0;
704 | 
705 |   // Row 1
706 |   {
707 |     values[nnz++] = -1;
708 |     values[nnz++] = 2;
709 | 
710 |     bs->rows.emplace_back();
711 |     CompressedRow& row = bs->rows.back();
712 |     row.block.size = 1;
713 |     row.block.position = 0;
714 |     row.cells.emplace_back(0, 0);
715 |     row.cells.emplace_back(4, 1);
716 |   }
717 | 
718 |   // Row 2
719 |   {
720 |     values[nnz++] = 3;
721 |     values[nnz++] = 4;
722 | 
723 |     bs->rows.emplace_back();
724 |     CompressedRow& row = bs->rows.back();
725 |     row.block.size = 1;
726 |     row.block.position = 1;
727 |     row.cells.emplace_back(0, 2);
728 |     row.cells.emplace_back(4, 3);
729 |   }
730 | 
731 |   // Row 3
732 |   {
733 |     values[nnz++] = -1;
734 |     values[nnz++] = 1;
735 | 
736 |     bs->rows.emplace_back();
737 |     CompressedRow& row = bs->rows.back();
738 |     row.block.size = 1;
739 |     row.block.position = 2;
740 |     row.cells.emplace_back(1, 4);
741 |     row.cells.emplace_back(3, 5);
742 |   }
743 | 
744 |   // Row 4
745 |   {
746 |     values[nnz++] = -3;
747 |     values[nnz++] = 1;
748 | 
749 |     bs->rows.emplace_back();
750 |     CompressedRow& row = bs->rows.back();
751 |     row.block.size = 1;
752 |     row.block.position = 3;
753 |     row.cells.emplace_back(1, 6);
754 |     row.cells.emplace_back(3, 7);
755 |   }
756 | 
757 |   // Row 5
758 |   {
759 |     values[nnz++] = -1;
760 |     values[nnz++] = 3;
761 | 
762 |     bs->rows.emplace_back();
763 |     CompressedRow& row = bs->rows.back();
764 |     row.block.size = 1;
765 |     row.block.position = 4;
766 |     row.cells.emplace_back(1, 8);
767 |     row.cells.emplace_back(2, 9);
768 |   }
769 | 
770 |   // Row 6
771 |   {
772 |     // values[nnz++] = 2;
773 |     values[nnz++] = -2;
774 |     values[nnz++] = 1;
775 | 
776 |     bs->rows.emplace_back();
777 |     CompressedRow& row = bs->rows.back();
778 |     row.block.size = 1;
779 |     row.block.position = 5;
780 |     // row.cells.emplace_back(0, 10);
781 |     row.cells.emplace_back(1, 10);
782 |     row.cells.emplace_back(2, 11);
783 |   }
784 | 
785 |   auto A = std::make_unique<BlockSparseMatrix>(bs);
786 |   memcpy(A->mutable_values(), values.get(), nnz * sizeof(*A->values()));
787 | 
788 |   for (int i = 0; i < num_cols; ++i) {
789 |     problem->D.get()[i] = 1;
790 |   }
791 | 
792 |   for (int i = 0; i < num_rows; ++i) {
793 |     problem->b.get()[i] = i;
794 |   }
795 | 
796 |   problem->A = std::move(A);
797 | 
798 |   return problem;
799 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 3

START → 1
1   int num_rows = 6
    int num_cols = 5
    problem->b = std::make_unique<double[]>(num_rows)
    problem->D = std::make_unique<double[]>(num_cols)
    problem->num_eliminate_blocks = 2
    problem->x = std::make_unique<double[]>(num_cols)
    problem->x[0] = 0.20000000000000001
    problem->x[1] = -1.4443999999999999
    problem->x[2] = 0.97770000000000001
    problem->x[3] = -0.38879999999999998
    problem->x[4] = 0.10000000000000001
    CFGNewAllocator(CompressedRowBlockStructure *)
    auto *bs = new CompressedRowBlockStructure
    int c = 0                                                      → 2
2   vòng for, điều kiện: c < num_cols                              đúng → 3   sai → 5
3   bs->cols.emplace_back()
    bs->cols.back().size = 1
    bs->cols.back().position = c                                   → 4
4   ++c                                                            → 2
5   int nnz = 0
    values[nnz++] = -1
    values[nnz++] = 2
    bs->rows.emplace_back()
    CompressedRow &row = bs->rows.back()
    row.block.size = 1
    row.block.position = 0
    row.cells.emplace_back(0, 0)
    row.cells.emplace_back(4, 1)
    values[nnz++] = 3
    values[nnz++] = 4
    bs->rows.emplace_back()
    CompressedRow &row = bs->rows.back()
    row.block.size = 1
    row.block.position = 1
    row.cells.emplace_back(0, 2)
    row.cells.emplace_back(4, 3)
    values[nnz++] = -1
    values[nnz++] = 1
    bs->rows.emplace_back()
    CompressedRow &row = bs->rows.back()
    row.block.size = 1
    row.block.position = 2
    row.cells.emplace_back(1, 4)
    row.cells.emplace_back(3, 5)
    values[nnz++] = -3
    values[nnz++] = 1
    bs->rows.emplace_back()
    CompressedRow &row = bs->rows.back()
    row.block.size = 1
    row.block.position = 3
    row.cells.emplace_back(1, 6)
    row.cells.emplace_back(3, 7)
    values[nnz++] = -1
    values[nnz++] = 3
    bs->rows.emplace_back()
    CompressedRow &row = bs->rows.back()
    row.block.size = 1
    row.block.position = 4
    row.cells.emplace_back(1, 8)
    row.cells.emplace_back(2, 9)
    values[nnz++] = -2
    values[nnz++] = 1
    bs->rows.emplace_back()
    CompressedRow &row = bs->rows.back()
    row.block.size = 1
    row.block.position = 5
    row.cells.emplace_back(1, 10)
    row.cells.emplace_back(2, 11)
    memcpy(A->mutable_values(), values.get(), nnz * sizeof (*A->values()))
    int i = 0                                                      → 6
6   vòng for, điều kiện: i < num_cols                              đúng → 7   sai → 9
7   problem->D.get()[i] = 1                                        → 8
8   ++i                                                            → 6
9   int i = 0                                                      → 10
10  vòng for, điều kiện: i < num_rows                              đúng → 11   sai → 13
11  problem->b.get()[i] = i                                        → 12
12  ++i                                                            → 10
13  problem->A = std::move(A)                                      → END
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
#include "ceres/linear_least_squares_problems.h"
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1187_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
