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
- **Vòng lặp:**
  - Có giới hạn số lần lặp n (ví dụ `for (i = 0; i < size; ...)`): test với **0, 1, 2, một số ở giữa, n−1, n** lần lặp; thêm **n+1** nếu làm được.
  - Không có giới hạn (lặp đến khi thoả một điều kiện, ví dụ `while (!done)`): test với **0, 1, 2** lần lặp và **mỗi cách thoát khỏi vòng lặp** (`break`, `return`, điều kiện sai) ít nhất 1 lần.
  - Số lần lặp nào không làm được thì ghi lý do.
- **`CHECK(...)`:** lệnh kiểm tra của thư viện glog mà Ceres dùng. Nếu điều kiện sai, chương trình **dừng ngay**. **Không** cố tình làm `CHECK` sai; ghi nhánh đó là "không test (làm chương trình dừng)".

---

# 3. ĐẦU VÀO

## 3.1. Unit cần test

- Hàm: `SolveImpl(BlockSparseMatrix * A, const double * b, const LinearSolver::PerSolveOptions & per_solve_options, double * x)`, trả về `LinearSolver::Summary`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::SchurComplementSolver`
- Vị trí: `internal/ceres/schur_complement_solver.cc`, dòng 100–158

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
100 | LinearSolver::Summary SchurComplementSolver::SolveImpl(
101 |     BlockSparseMatrix* A,
102 |     const double* b,
103 |     const LinearSolver::PerSolveOptions& per_solve_options,
104 |     double* x) {
105 |   EventLogger event_logger("SchurComplementSolver::Solve");
106 | 
107 |   const CompressedRowBlockStructure* bs = A->block_structure();
108 |   if (eliminator_ == nullptr) {
109 |     const int num_eliminate_blocks = options_.elimination_groups[0];
110 |     const int num_f_blocks = bs->cols.size() - num_eliminate_blocks;
111 | 
112 |     InitStorage(bs);
113 |     DetectStructure(*bs,
114 |                     num_eliminate_blocks,
115 |                     &options_.row_block_size,
116 |                     &options_.e_block_size,
117 |                     &options_.f_block_size);
118 | 
119 |     // For the special case of the static structure <2,3,6> with
120 |     // exactly one f block use the SchurEliminatorForOneFBlock.
121 |     //
122 |     // TODO(sameeragarwal): A more scalable template specialization
123 |     // mechanism that does not cause binary bloat.
124 |     if (options_.row_block_size == 2 && options_.e_block_size == 3 &&
125 |         options_.f_block_size == 6 && num_f_blocks == 1) {
126 |       eliminator_ = std::make_unique<SchurEliminatorForOneFBlock<2, 3, 6>>();
127 |     } else {
128 |       eliminator_ = SchurEliminatorBase::Create(options_);
129 |     }
130 | 
131 |     CHECK(eliminator_);
132 |     const bool kFullRankETE = true;
133 |     eliminator_->Init(num_eliminate_blocks, kFullRankETE, bs);
134 |   }
135 | 
136 |   std::fill(x, x + A->num_cols(), 0.0);
137 |   event_logger.AddEvent("Setup");
138 | 
139 |   eliminator_->Eliminate(BlockSparseMatrixData(*A),
140 |                          b,
141 |                          per_solve_options.D,
142 |                          lhs_.get(),
143 |                          rhs_.data());
144 |   event_logger.AddEvent("Eliminate");
145 | 
146 |   double* reduced_solution = x + A->num_cols() - lhs_->num_cols();
147 |   const LinearSolver::Summary summary =
148 |       SolveReducedLinearSystem(per_solve_options, reduced_solution);
149 |   event_logger.AddEvent("ReducedSolve");
150 | 
151 |   if (summary.termination_type == LinearSolverTerminationType::SUCCESS) {
152 |     eliminator_->BackSubstitute(
153 |         BlockSparseMatrixData(*A), b, per_solve_options.D, reduced_solution, x);
154 |     event_logger.AddEvent("BackSubstitute");
155 |   }
156 | 
157 |   return summary;
158 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 3 (và 1 lệnh CHECK)

START → 1
1   "SchurComplementSolver::Solve"
    const CompressedRowBlockStructure *bs = A->block_structure()   → 2
2   if (eliminator_ == nullptr)                                    đúng → 3   sai → 7
3   const int num_eliminate_blocks = options_.elimination_groups[0]
    const int num_f_blocks = bs->cols.size() - num_eliminate_blocks
    InitStorage(bs)
    DetectStructure(*bs, num_eliminate_blocks, &options_.row_block_size, &options_.e_block_size, &options_.f_block_size)   → 4
4   if (options_.row_block_size == 2 && options_.e_block_size == 3 && options_.f_block_size == 6 && num_f_blocks == 1)   đúng → 5   sai → 10
5   eliminator_ = std::make_unique<SchurEliminatorForOneFBlock<2, 3, 6>>()   → 6
6   CHECK(eliminator_)                                             đúng → 7   sai → DỪNG
7   std::fill(x, x + A->num_cols(), 0.)
    event_logger.AddEvent("Setup")
    eliminator_->Eliminate(BlockSparseMatrixData(*A), b, per_solve_options.D, lhs_.get(), rhs_.data())
    event_logger.AddEvent("Eliminate")
    double *reduced_solution = x + A->num_cols() - lhs_->num_cols()
    SolveReducedLinearSystem(per_solve_options, reduced_solution)
    event_logger.AddEvent("ReducedSolve")                          → 8
8   if (summary.termination_type == LinearSolverTerminationType::SUCCESS)   đúng → 9   sai → END
9   eliminator_->BackSubstitute(BlockSparseMatrixData(*A), b, per_solve_options.D, reduced_solution, x)
    event_logger.AddEvent("BackSubstitute")                        → END
10  eliminator_ = SchurEliminatorBase::Create(options_)            → 6
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
#include "ceres/block_random_access_matrix.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/linear_solver.h"
#include "ceres/schur_complement_solver.h"
#include "ceres/schur_eliminator.h"
#include "ceres/wall_time.h"
```

- Đây là method của class `ceres::internal::SchurComplementSolver`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `SchurComplementSolver`:
Các constructor:
```cpp
  SchurComplementSolver(const LinearSolver::Options & options)
```
- Class có hàm **thuần ảo** (chưa có code, phải viết ở class con) nên không tạo object trực tiếp được: viết một class con kế thừa và viết các hàm: `InitStorage(const CompressedRowBlockStructure *)`, `SolveReducedLinearSystem(const LinearSolver::PerSolveOptions &, double *)`.

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1443_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
