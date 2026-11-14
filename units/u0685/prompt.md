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

- Hàm: `Init(const Solver::Options & options)`, trả về `void`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::Minimizer::Options`
- Vị trí: `internal/ceres/minimizer.h`, dòng 63–112

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
 63 |     void Init(const Solver::Options& options) {
 64 |       num_threads = options.num_threads;
 65 |       max_num_iterations = options.max_num_iterations;
 66 |       max_solver_time_in_seconds = options.max_solver_time_in_seconds;
 67 |       max_step_solver_retries = 5;
 68 |       gradient_tolerance = options.gradient_tolerance;
 69 |       parameter_tolerance = options.parameter_tolerance;
 70 |       function_tolerance = options.function_tolerance;
 71 |       min_relative_decrease = options.min_relative_decrease;
 72 |       eta = options.eta;
 73 |       jacobi_scaling = options.jacobi_scaling;
 74 |       use_nonmonotonic_steps = options.use_nonmonotonic_steps;
 75 |       max_consecutive_nonmonotonic_steps =
 76 |           options.max_consecutive_nonmonotonic_steps;
 77 |       trust_region_problem_dump_directory =
 78 |           options.trust_region_problem_dump_directory;
 79 |       trust_region_minimizer_iterations_to_dump =
 80 |           options.trust_region_minimizer_iterations_to_dump;
 81 |       trust_region_problem_dump_format_type =
 82 |           options.trust_region_problem_dump_format_type;
 83 |       max_num_consecutive_invalid_steps =
 84 |           options.max_num_consecutive_invalid_steps;
 85 |       min_trust_region_radius = options.min_trust_region_radius;
 86 |       line_search_direction_type = options.line_search_direction_type;
 87 |       line_search_type = options.line_search_type;
 88 |       nonlinear_conjugate_gradient_type =
 89 |           options.nonlinear_conjugate_gradient_type;
 90 |       max_lbfgs_rank = options.max_lbfgs_rank;
 91 |       use_approximate_eigenvalue_bfgs_scaling =
 92 |           options.use_approximate_eigenvalue_bfgs_scaling;
 93 |       line_search_interpolation_type = options.line_search_interpolation_type;
 94 |       min_line_search_step_size = options.min_line_search_step_size;
 95 |       line_search_sufficient_function_decrease =
 96 |           options.line_search_sufficient_function_decrease;
 97 |       max_line_search_step_contraction =
 98 |           options.max_line_search_step_contraction;
 99 |       min_line_search_step_contraction =
100 |           options.min_line_search_step_contraction;
101 |       max_num_line_search_step_size_iterations =
102 |           options.max_num_line_search_step_size_iterations;
103 |       max_num_line_search_direction_restarts =
104 |           options.max_num_line_search_direction_restarts;
105 |       line_search_sufficient_curvature_decrease =
106 |           options.line_search_sufficient_curvature_decrease;
107 |       max_line_search_step_expansion = options.max_line_search_step_expansion;
108 |       inner_iteration_tolerance = options.inner_iteration_tolerance;
109 |       is_silent = (options.logging_type == SILENT);
110 |       is_constrained = false;
111 |       callbacks = options.callbacks;
112 |     }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 0

START → 1
1   num_threads = options.num_threads
    max_num_iterations = options.max_num_iterations
    max_solver_time_in_seconds = options.max_solver_time_in_seconds
    max_step_solver_retries = 5
    gradient_tolerance = options.gradient_tolerance
    parameter_tolerance = options.parameter_tolerance
    function_tolerance = options.function_tolerance
    min_relative_decrease = options.min_relative_decrease
    eta = options.eta
    jacobi_scaling = options.jacobi_scaling
    use_nonmonotonic_steps = options.use_nonmonotonic_steps
    max_consecutive_nonmonotonic_steps = options.max_consecutive_nonmonotonic_steps
    trust_region_problem_dump_directory = options.trust_region_problem_dump_directory
    trust_region_minimizer_iterations_to_dump = options.trust_region_minimizer_iterations_to_dump
    trust_region_problem_dump_format_type = options.trust_region_problem_dump_format_type
    max_num_consecutive_invalid_steps = options.max_num_consecutive_invalid_steps
    min_trust_region_radius = options.min_trust_region_radius
    line_search_direction_type = options.line_search_direction_type
    line_search_type = options.line_search_type
    nonlinear_conjugate_gradient_type = options.nonlinear_conjugate_gradient_type
    max_lbfgs_rank = options.max_lbfgs_rank
    use_approximate_eigenvalue_bfgs_scaling = options.use_approximate_eigenvalue_bfgs_scaling
    line_search_interpolation_type = options.line_search_interpolation_type
    min_line_search_step_size = options.min_line_search_step_size
    line_search_sufficient_function_decrease = options.line_search_sufficient_function_decrease
    max_line_search_step_contraction = options.max_line_search_step_contraction
    min_line_search_step_contraction = options.min_line_search_step_contraction
    max_num_line_search_step_size_iterations = options.max_num_line_search_step_size_iterations
    max_num_line_search_direction_restarts = options.max_num_line_search_direction_restarts
    line_search_sufficient_curvature_decrease = options.line_search_sufficient_curvature_decrease
    max_line_search_step_expansion = options.max_line_search_step_expansion
    inner_iteration_tolerance = options.inner_iteration_tolerance
    is_silent = (options.logging_type == SILENT)
    is_constrained = false
    callbacks = options.callbacks                                  → END
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
#include "ceres/solver.h"
#include "ceres/minimizer.h"
```

- Đây là method của class `ceres::internal::Minimizer::Options`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `Options`:
Các constructor:
```cpp
  Options()
  Options(const Solver::Options & options)
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u0685_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
