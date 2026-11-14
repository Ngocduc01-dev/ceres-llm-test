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

- Hàm: `Solve(const GradientProblemSolver::Options & options, const GradientProblem & problem, double * parameters_ptr, GradientProblemSolver::Summary * summary)`, trả về `void`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::GradientProblemSolver`
- Vị trí: `internal/ceres/gradient_problem_solver.cc`, dòng 98–201

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
 98 | void GradientProblemSolver::Solve(const GradientProblemSolver::Options& options,
 99 |                                   const GradientProblem& problem,
100 |                                   double* parameters_ptr,
101 |                                   GradientProblemSolver::Summary* summary) {
102 |   using internal::CallStatistics;
103 |   using internal::GradientProblemEvaluator;
104 |   using internal::GradientProblemSolverStateUpdatingCallback;
105 |   using internal::LoggingCallback;
106 |   using internal::Minimizer;
107 |   using internal::SetSummaryFinalCost;
108 |   using internal::WallTimeInSeconds;
109 | 
110 |   double start_time = WallTimeInSeconds();
111 | 
112 |   CHECK(summary != nullptr);
113 |   *summary = Summary();
114 |   // clang-format off
115 |   summary->num_parameters                    = problem.NumParameters();
116 |   summary->num_tangent_parameters            = problem.NumTangentParameters();
117 |   summary->line_search_direction_type        = options.line_search_direction_type;         //  NOLINT
118 |   summary->line_search_interpolation_type    = options.line_search_interpolation_type;     //  NOLINT
119 |   summary->line_search_type                  = options.line_search_type;
120 |   summary->max_lbfgs_rank                    = options.max_lbfgs_rank;
121 |   summary->nonlinear_conjugate_gradient_type = options.nonlinear_conjugate_gradient_type;  //  NOLINT
122 |   // clang-format on
123 | 
124 |   // Check validity
125 |   if (!options.IsValid(&summary->message)) {
126 |     LOG(ERROR) << "Terminating: " << summary->message;
127 |     return;
128 |   }
129 | 
130 |   VectorRef parameters(parameters_ptr, problem.NumParameters());
131 |   Vector solution(problem.NumParameters());
132 |   solution = parameters;
133 | 
134 |   // TODO(sameeragarwal): This is a bit convoluted, we should be able
135 |   // to convert to minimizer options directly, but this will do for
136 |   // now.
137 |   Minimizer::Options minimizer_options =
138 |       Minimizer::Options(GradientProblemSolverOptionsToSolverOptions(options));
139 |   minimizer_options.evaluator =
140 |       std::make_unique<GradientProblemEvaluator>(problem);
141 | 
142 |   std::unique_ptr<IterationCallback> logging_callback;
143 |   if (options.logging_type != SILENT) {
144 |     logging_callback = std::make_unique<LoggingCallback>(
145 |         LINE_SEARCH, options.minimizer_progress_to_stdout);
146 |     minimizer_options.callbacks.insert(minimizer_options.callbacks.begin(),
147 |                                        logging_callback.get());
148 |   }
149 | 
150 |   std::unique_ptr<IterationCallback> state_updating_callback;
151 |   if (options.update_state_every_iteration) {
152 |     state_updating_callback =
153 |         std::make_unique<GradientProblemSolverStateUpdatingCallback>(
154 |             problem.NumParameters(), solution.data(), parameters_ptr);
155 |     minimizer_options.callbacks.insert(minimizer_options.callbacks.begin(),
156 |                                        state_updating_callback.get());
157 |   }
158 | 
159 |   std::unique_ptr<Minimizer> minimizer(Minimizer::Create(LINE_SEARCH));
160 | 
161 |   Solver::Summary solver_summary;
162 |   solver_summary.fixed_cost = 0.0;
163 |   solver_summary.preprocessor_time_in_seconds = 0.0;
164 |   solver_summary.postprocessor_time_in_seconds = 0.0;
165 |   solver_summary.line_search_polynomial_minimization_time_in_seconds = 0.0;
166 | 
167 |   minimizer->Minimize(minimizer_options, solution.data(), &solver_summary);
168 | 
169 |   // clang-format off
170 |   summary->termination_type = solver_summary.termination_type;
171 |   summary->message          = solver_summary.message;
172 |   summary->initial_cost     = solver_summary.initial_cost;
173 |   summary->final_cost       = solver_summary.final_cost;
174 |   summary->iterations       = solver_summary.iterations;
175 |   // clang-format on
176 |   summary->line_search_polynomial_minimization_time_in_seconds =
177 |       solver_summary.line_search_polynomial_minimization_time_in_seconds;
178 | 
179 |   if (summary->IsSolutionUsable()) {
180 |     parameters = solution;
181 |     SetSummaryFinalCost(summary);
182 |   }
183 | 
184 |   const std::map<std::string, CallStatistics>& evaluator_statistics =
185 |       minimizer_options.evaluator->Statistics();
186 |   {
187 |     const CallStatistics& call_stats = FindWithDefault(
188 |         evaluator_statistics, "Evaluator::Residual", CallStatistics());
189 |     summary->cost_evaluation_time_in_seconds = call_stats.time;
190 |     summary->num_cost_evaluations = call_stats.calls;
191 |   }
192 | 
193 |   {
194 |     const CallStatistics& call_stats = FindWithDefault(
195 |         evaluator_statistics, "Evaluator::Jacobian", CallStatistics());
196 |     summary->gradient_evaluation_time_in_seconds = call_stats.time;
197 |     summary->num_gradient_evaluations = call_stats.calls;
198 |   }
199 | 
200 |   summary->total_time_in_seconds = WallTimeInSeconds() - start_time;
201 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 4 (và 1 lệnh CHECK)

START → 1
1   double start_time = WallTimeInSeconds()                        → 2
2   CHECK(summary != nullptr)                                      đúng → 3   sai → DỪNG
3   *summary = Summary()
    summary->num_parameters = problem.NumParameters()
    summary->num_tangent_parameters = problem.NumTangentParameters()
    summary->line_search_direction_type = options.line_search_direction_type
    summary->line_search_interpolation_type = options.line_search_interpolation_type
    summary->line_search_type = options.line_search_type
    summary->max_lbfgs_rank = options.max_lbfgs_rank
    summary->nonlinear_conjugate_gradient_type = options.nonlinear_conjugate_gradient_type   → 4
4   if (!options.IsValid(&summary->message))                       đúng → END   sai → 5
5   parameters_ptr, problem.NumParameters()
    solution = parameters
    Minimizer::Options(GradientProblemSolverOptionsToSolverOptions(options))
    minimizer_options.evaluator = std::make_unique<GradientProblemEvaluator>(problem)   → 6
6   if (options.logging_type != SILENT)                            đúng → 7   sai → 8
7   logging_callback = std::make_unique<LoggingCallback>(LINE_SEARCH, options.minimizer_progress_to_stdout)   → 8
8   if (options.update_state_every_iteration)                      đúng → 9   sai → 10
9   state_updating_callback = std::make_unique<GradientProblemSolverStateUpdatingCallback>(problem.NumParameters(), solution.data(), parameters_ptr)   → 10
10  solver_summary.fixed_cost = 0.
    solver_summary.preprocessor_time_in_seconds = 0.
    solver_summary.postprocessor_time_in_seconds = 0.
    solver_summary.line_search_polynomial_minimization_time_in_seconds = 0.
    minimizer->Minimize(minimizer_options, solution.data(), &solver_summary)
    summary->termination_type = solver_summary.termination_type
    summary->message = solver_summary.message
    summary->initial_cost = solver_summary.initial_cost
    summary->final_cost = solver_summary.final_cost
    summary->iterations = solver_summary.iterations
    summary->line_search_polynomial_minimization_time_in_seconds = solver_summary.line_search_polynomial_minimization_time_in_seconds   → 11
11  if (summary->IsSolutionUsable())                               đúng → 12   sai → 13
12  parameters = solution
    SetSummaryFinalCost(summary)                                   → 13
13  const std::map<std::string, CallStatistics> &evaluator_statistics = minimizer_options.evaluator->Statistics()
    const CallStatistics &call_stats = FindWithDefault(evaluator_statistics, "Evaluator::Residual", CallStatistics())
    summary->cost_evaluation_time_in_seconds = call_stats.time
    summary->num_cost_evaluations = call_stats.calls
    const CallStatistics &call_stats = FindWithDefault(evaluator_statistics, "Evaluator::Jacobian", CallStatistics())
    summary->gradient_evaluation_time_in_seconds = call_stats.time
    summary->num_gradient_evaluations = call_stats.calls
    summary->total_time_in_seconds = WallTimeInSeconds() - start_time   → END
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
#include "ceres/gradient_problem.h"
#include "ceres/gradient_problem_solver.h"
#include "ceres/iteration_callback.h"
#include "ceres/solver.h"
#include "ceres/callbacks.h"
#include "ceres/evaluator.h"
#include "ceres/execution_summary.h"
#include "ceres/gradient_problem_evaluator.h"
#include "ceres/map_util.h"
#include "ceres/minimizer.h"
#include "ceres/solver_utils.h"
```

- Đây là method của class `ceres::GradientProblemSolver`: tạo một object của class rồi gọi method trên object đó.

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1537_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
