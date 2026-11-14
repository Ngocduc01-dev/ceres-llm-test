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

- Hàm: `GradientProblemSolverOptionsToSolverOptions(const GradientProblemSolver::Options & options)`, trả về `Solver::Options`
- Loại: hàm tự do (không thuộc class)
- Namespace: `ceres::(namespace không tên)`
- Vị trí: `internal/ceres/gradient_problem_solver.cc`, dòng 56–86

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
56 | Solver::Options GradientProblemSolverOptionsToSolverOptions(
57 |     const GradientProblemSolver::Options& options) {
58 | #define COPY_OPTION(x) solver_options.x = options.x
59 | 
60 |   Solver::Options solver_options;
61 |   solver_options.minimizer_type = LINE_SEARCH;
62 |   COPY_OPTION(line_search_direction_type);
63 |   COPY_OPTION(line_search_type);
64 |   COPY_OPTION(nonlinear_conjugate_gradient_type);
65 |   COPY_OPTION(max_lbfgs_rank);
66 |   COPY_OPTION(use_approximate_eigenvalue_bfgs_scaling);
67 |   COPY_OPTION(line_search_interpolation_type);
68 |   COPY_OPTION(min_line_search_step_size);
69 |   COPY_OPTION(line_search_sufficient_function_decrease);
70 |   COPY_OPTION(max_line_search_step_contraction);
71 |   COPY_OPTION(min_line_search_step_contraction);
72 |   COPY_OPTION(max_num_line_search_step_size_iterations);
73 |   COPY_OPTION(max_num_line_search_direction_restarts);
74 |   COPY_OPTION(line_search_sufficient_curvature_decrease);
75 |   COPY_OPTION(max_line_search_step_expansion);
76 |   COPY_OPTION(max_num_iterations);
77 |   COPY_OPTION(max_solver_time_in_seconds);
78 |   COPY_OPTION(parameter_tolerance);
79 |   COPY_OPTION(function_tolerance);
80 |   COPY_OPTION(gradient_tolerance);
81 |   COPY_OPTION(logging_type);
82 |   COPY_OPTION(minimizer_progress_to_stdout);
83 |   COPY_OPTION(callbacks);
84 |   return solver_options;
85 | #undef COPY_OPTION
86 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 0

START → 1
1   solver_options.minimizer_type = LINE_SEARCH
    solver_options.line_search_direction_type = options.line_search_direction_type
    solver_options.line_search_type = options.line_search_type
    solver_options.nonlinear_conjugate_gradient_type = options.nonlinear_conjugate_gradient_type
    solver_options.max_lbfgs_rank = options.max_lbfgs_rank
    solver_options.use_approximate_eigenvalue_bfgs_scaling = options.use_approximate_eigenvalue_bfgs_scaling
    solver_options.line_search_interpolation_type = options.line_search_interpolation_type
    solver_options.min_line_search_step_size = options.min_line_search_step_size
    solver_options.line_search_sufficient_function_decrease = options.line_search_sufficient_function_decrease
    solver_options.max_line_search_step_contraction = options.max_line_search_step_contraction
    solver_options.min_line_search_step_contraction = options.min_line_search_step_contraction
    solver_options.max_num_line_search_step_size_iterations = options.max_num_line_search_step_size_iterations
    solver_options.max_num_line_search_direction_restarts = options.max_num_line_search_direction_restarts
    solver_options.line_search_sufficient_curvature_decrease = options.line_search_sufficient_curvature_decrease
    solver_options.max_line_search_step_expansion = options.max_line_search_step_expansion
    solver_options.max_num_iterations = options.max_num_iterations
    solver_options.max_solver_time_in_seconds = options.max_solver_time_in_seconds
    solver_options.parameter_tolerance = options.parameter_tolerance
    solver_options.function_tolerance = options.function_tolerance
    solver_options.gradient_tolerance = options.gradient_tolerance
    solver_options.logging_type = options.logging_type
    solver_options.minimizer_progress_to_stdout = options.minimizer_progress_to_stdout
    solver_options.callbacks = options.callbacks                   → END
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
#include "ceres/gradient_problem_solver.h"
#include "ceres/solver.h"
#include "ceres/gradient_problem_solver.cc"
```

- Hàm này chỉ dùng được bên trong file `internal/ceres/gradient_problem_solver.cc` (khai báo `static` hoặc trong namespace không tên). Để gọi được, thêm `#include "ceres/gradient_problem_solver.cc"` vào file test.

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u0790_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
