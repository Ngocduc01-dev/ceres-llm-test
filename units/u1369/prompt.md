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

- Hàm: `ConjugateGradientsSolver(const ConjugateGradientsSolverOptions options, ConjugateGradientsLinearOperator<DenseVectorType>& lhs, const DenseVectorType& rhs, ConjugateGradientsLinearOperator<DenseVectorType>& preconditioner, DenseVectorType* scratch[4], DenseVectorType& solution)`, trả về `LinearSolver::Summary`
- Loại: hàm template (hàm mẫu, kiểu dữ liệu được điền khi dùng)
- Namespace: `ceres::internal`
- Vị trí: `internal/ceres/conjugate_gradients_solver.h`, dòng 108–305

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
108 | template <typename DenseVectorType>
109 | LinearSolver::Summary ConjugateGradientsSolver(
110 |     const ConjugateGradientsSolverOptions options,
111 |     ConjugateGradientsLinearOperator<DenseVectorType>& lhs,
112 |     const DenseVectorType& rhs,
113 |     ConjugateGradientsLinearOperator<DenseVectorType>& preconditioner,
114 |     DenseVectorType* scratch[4],
115 |     DenseVectorType& solution) {
116 |   auto IsZeroOrInfinity = [](double x) {
117 |     return ((x == 0.0) || std::isinf(x));
118 |   };
119 | 
120 |   DenseVectorType& p = *scratch[0];
121 |   DenseVectorType& r = *scratch[1];
122 |   DenseVectorType& z = *scratch[2];
123 |   DenseVectorType& tmp = *scratch[3];
124 | 
125 |   LinearSolver::Summary summary;
126 |   summary.termination_type = LinearSolverTerminationType::NO_CONVERGENCE;
127 |   summary.message = "Maximum number of iterations reached.";
128 |   summary.num_iterations = 0;
129 | 
130 |   const double norm_rhs = Norm(rhs, options.context, options.num_threads);
131 |   if (norm_rhs == 0.0) {
132 |     SetZero(solution, options.context, options.num_threads);
133 |     summary.termination_type = LinearSolverTerminationType::SUCCESS;
134 |     summary.message = "Convergence. |b| = 0.";
135 |     return summary;
136 |   }
137 | 
138 |   const double tol_r = options.r_tolerance * norm_rhs;
139 | 
140 |   SetZero(tmp, options.context, options.num_threads);
141 |   lhs.RightMultiplyAndAccumulate(solution, tmp);
142 | 
143 |   // r = rhs - tmp
144 |   Axpby(1.0, rhs, -1.0, tmp, r, options.context, options.num_threads);
145 | 
146 |   double norm_r = Norm(r, options.context, options.num_threads);
147 |   if (options.min_num_iterations == 0 && norm_r <= tol_r) {
148 |     summary.termination_type = LinearSolverTerminationType::SUCCESS;
149 |     summary.message =
150 |         StringPrintf("Convergence. |r| = %e <= %e.", norm_r, tol_r);
151 |     return summary;
152 |   }
153 | 
154 |   double rho = 1.0;
155 | 
156 |   // Initial value of the quadratic model Q = x'Ax - 2 * b'x.
157 |   // double Q0 = -1.0 * solution.dot(rhs + r);
158 |   Axpby(1.0, rhs, 1.0, r, tmp, options.context, options.num_threads);
159 |   double Q0 = -Dot(solution, tmp, options.context, options.num_threads);
160 | 
161 |   for (summary.num_iterations = 1;; ++summary.num_iterations) {
162 |     SetZero(z, options.context, options.num_threads);
163 |     preconditioner.RightMultiplyAndAccumulate(r, z);
164 | 
165 |     const double last_rho = rho;
166 |     // rho = r.dot(z);
167 |     rho = Dot(r, z, options.context, options.num_threads);
168 |     if (IsZeroOrInfinity(rho)) {
169 |       summary.termination_type = LinearSolverTerminationType::FAILURE;
170 |       summary.message = StringPrintf("Numerical failure. rho = r'z = %e.", rho);
171 |       break;
172 |     }
173 | 
174 |     if (summary.num_iterations == 1) {
175 |       Copy(z, p, options.context, options.num_threads);
176 |     } else {
177 |       const double beta = rho / last_rho;
178 |       if (IsZeroOrInfinity(beta)) {
179 |         summary.termination_type = LinearSolverTerminationType::FAILURE;
180 |         summary.message = StringPrintf(
181 |             "Numerical failure. beta = rho_n / rho_{n-1} = %e, "
182 |             "rho_n = %e, rho_{n-1} = %e",
183 |             beta,
184 |             rho,
185 |             last_rho);
186 |         break;
187 |       }
188 |       // p = z + beta * p;
189 |       Axpby(1.0, z, beta, p, p, options.context, options.num_threads);
190 |     }
191 | 
192 |     DenseVectorType& q = z;
193 |     SetZero(q, options.context, options.num_threads);
194 |     lhs.RightMultiplyAndAccumulate(p, q);
195 |     const double pq = Dot(p, q, options.context, options.num_threads);
196 |     if ((pq <= 0) || std::isinf(pq)) {
197 |       summary.termination_type = LinearSolverTerminationType::NO_CONVERGENCE;
198 |       summary.message = StringPrintf(
199 |           "Matrix is indefinite, no more progress can be made. "
200 |           "p'q = %e. |p| = %e, |q| = %e",
201 |           pq,
202 |           Norm(p, options.context, options.num_threads),
203 |           Norm(q, options.context, options.num_threads));
204 |       break;
205 |     }
206 | 
207 |     const double alpha = rho / pq;
208 |     if (std::isinf(alpha)) {
209 |       summary.termination_type = LinearSolverTerminationType::FAILURE;
210 |       summary.message = StringPrintf(
211 |           "Numerical failure. alpha = rho / pq = %e, rho = %e, pq = %e.",
212 |           alpha,
213 |           rho,
214 |           pq);
215 |       break;
216 |     }
217 | 
218 |     // solution = solution + alpha * p;
219 |     Axpby(1.0,
220 |           solution,
221 |           alpha,
222 |           p,
223 |           solution,
224 |           options.context,
225 |           options.num_threads);
226 | 
227 |     // Ideally we would just use the update r = r - alpha*q to keep
228 |     // track of the residual vector. However this estimate tends to
229 |     // drift over time due to round off errors. Thus every
230 |     // residual_reset_period iterations, we calculate the residual as
231 |     // r = b - Ax. We do not do this every iteration because this
232 |     // requires an additional matrix vector multiply which would
233 |     // double the complexity of the CG algorithm.
234 |     if (summary.num_iterations % options.residual_reset_period == 0) {
235 |       SetZero(tmp, options.context, options.num_threads);
236 |       lhs.RightMultiplyAndAccumulate(solution, tmp);
237 |       Axpby(1.0, rhs, -1.0, tmp, r, options.context, options.num_threads);
238 |       // r = rhs - tmp;
239 |     } else {
240 |       Axpby(1.0, r, -alpha, q, r, options.context, options.num_threads);
241 |       // r = r - alpha * q;
242 |     }
243 | 
244 |     // Quadratic model based termination.
245 |     //   Q1 = x'Ax - 2 * b' x.
246 |     // const double Q1 = -1.0 * solution.dot(rhs + r);
247 |     Axpby(1.0, rhs, 1.0, r, tmp, options.context, options.num_threads);
248 |     const double Q1 = -Dot(solution, tmp, options.context, options.num_threads);
249 | 
250 |     // For PSD matrices A, let
251 |     //
252 |     //   Q(x) = x'Ax - 2b'x
253 |     //
254 |     // be the cost of the quadratic function defined by A and b. Then,
255 |     // the solver terminates at iteration i if
256 |     //
257 |     //   i * (Q(x_i) - Q(x_i-1)) / Q(x_i) < q_tolerance.
258 |     //
259 |     // This termination criterion is more useful when using CG to
260 |     // solve the Newton step. This particular convergence test comes
261 |     // from Stephen Nash's work on truncated Newton
262 |     // methods. References:
263 |     //
264 |     //   1. Stephen G. Nash & Ariela Sofer, Assessing A Search
265 |     //   Direction Within A Truncated Newton Method, Operation
266 |     //   Research Letters 9(1990) 219-221.
267 |     //
268 |     //   2. Stephen G. Nash, A Survey of Truncated Newton Methods,
269 |     //   Journal of Computational and Applied Mathematics,
270 |     //   124(1-2), 45-59, 2000.
271 |     //
272 |     const double zeta = summary.num_iterations * (Q1 - Q0) / Q1;
273 |     if (zeta < options.q_tolerance &&
274 |         summary.num_iterations >= options.min_num_iterations) {
275 |       summary.termination_type = LinearSolverTerminationType::SUCCESS;
276 |       summary.message =
277 |           StringPrintf("Iteration: %d Convergence: zeta = %e < %e. |r| = %e",
278 |                        summary.num_iterations,
279 |                        zeta,
280 |                        options.q_tolerance,
281 |                        Norm(r, options.context, options.num_threads));
282 |       break;
283 |     }
284 |     Q0 = Q1;
285 | 
286 |     // Residual based termination.
287 |     norm_r = Norm(r, options.context, options.num_threads);
288 |     if (norm_r <= tol_r &&
289 |         summary.num_iterations >= options.min_num_iterations) {
290 |       summary.termination_type = LinearSolverTerminationType::SUCCESS;
291 |       summary.message =
292 |           StringPrintf("Iteration: %d Convergence. |r| = %e <= %e.",
293 |                        summary.num_iterations,
294 |                        norm_r,
295 |                        tol_r);
296 |       break;
297 |     }
298 | 
299 |     if (summary.num_iterations >= options.max_num_iterations) {
300 |       break;
301 |     }
302 |   }
303 | 
304 |   return summary;
305 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Ghi chú: đây là template – một số kiểu dữ liệu còn để trống, chỉ được điền khi dùng. CFG dưới đây dựng cho trường hợp ConjugateGradientsSolver<Matrix<double, -1, 1>>.

Số điểm rẽ nhánh: 11

START → 1
1   auto IsZeroOrInfinity = [](double x) {
    Eigen::Matrix<double, -1, 1> &p = *scratch[0]
    Eigen::Matrix<double, -1, 1> &r = *scratch[1]
    Eigen::Matrix<double, -1, 1> &z = *scratch[2]
    Eigen::Matrix<double, -1, 1> &tmp = *scratch[3]
    summary.termination_type = LinearSolverTerminationType::NO_CONVERGENCE
    summary.message = "Maximum number of iterations reached."
    summary.num_iterations = 0
    const double norm_rhs = Norm(rhs, options.context, options.num_threads)   → 2
2   if (norm_rhs == 0.)                                            đúng → 3   sai → 4
3   SetZero(solution, options.context, options.num_threads)
    summary.termination_type = LinearSolverTerminationType::SUCCESS
    summary.message = "Convergence. |b| = 0."                      → END
4   const double tol_r = options.r_tolerance * norm_rhs
    SetZero(tmp, options.context, options.num_threads)
    lhs.RightMultiplyAndAccumulate(solution, tmp)
    Axpby(1., rhs, -1., tmp, r, options.context, options.num_threads)
    double norm_r = Norm(r, options.context, options.num_threads)   → 5
5   if (options.min_num_iterations == 0 && norm_r <= tol_r)        đúng → 6   sai → 7
6   summary.termination_type = LinearSolverTerminationType::SUCCESS
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    summary.message = StringPrintf("Convergence. |r| = %e <= %e.", norm_r, tol_r)   → END
7   double rho = 1.
    Axpby(1., rhs, 1., r, tmp, options.context, options.num_threads)
    double Q0 = -Dot(solution, tmp, options.context, options.num_threads)
    summary.num_iterations = 1                                     → 8
8   vòng for, điều kiện:                                           → 9
9   SetZero(z, options.context, options.num_threads)
    preconditioner.RightMultiplyAndAccumulate(r, z)
    const double last_rho = rho
    rho = Dot(r, z, options.context, options.num_threads)          → 10
10  if (IsZeroOrInfinity(rho))                                     đúng → 11   sai → 12
11  summary.termination_type = LinearSolverTerminationType::FAILURE
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    summary.message = StringPrintf("Numerical failure. rho = r'z = %e.", rho)
    break                                                          → END
12  if (summary.num_iterations == 1)                               đúng → 13   sai → 33
13  Copy(z, p, options.context, options.num_threads)               → 14
14  Eigen::Matrix<double, -1, 1> &q = z
    SetZero(q, options.context, options.num_threads)
    lhs.RightMultiplyAndAccumulate(p, q)
    const double pq = Dot(p, q, options.context, options.num_threads)   → 15
15  if (pq <= 0) || std::isinf(pq)                                 đúng → 16   sai → 17
16  summary.termination_type = LinearSolverTerminationType::NO_CONVERGENCE
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    summary.message = StringPrintf("Matrix is indefinite, no more progress can be made. p'q = %e. |p| = %e, |q| = %e", pq, Norm(p, options.context, options.num_threads), Norm(q, options.context, options.num_threads))
    break                                                          → END
17  const double alpha = rho / pq                                  → 18
18  if (std::isinf(alpha))                                         đúng → 19   sai → 20
19  summary.termination_type = LinearSolverTerminationType::FAILURE
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    summary.message = StringPrintf("Numerical failure. alpha = rho / pq = %e, rho = %e, pq = %e.", alpha, rho, pq)
    break                                                          → END
20  Axpby(1., solution, alpha, p, solution, options.context, options.num_threads)   → 21
21  if (summary.num_iterations % options.residual_reset_period == 0)   đúng → 22   sai → 32
22  SetZero(tmp, options.context, options.num_threads)
    lhs.RightMultiplyAndAccumulate(solution, tmp)
    Axpby(1., rhs, -1., tmp, r, options.context, options.num_threads)   → 23
23  Axpby(1., rhs, 1., r, tmp, options.context, options.num_threads)
    const double Q1 = -Dot(solution, tmp, options.context, options.num_threads)
    const double zeta = summary.num_iterations * (Q1 - Q0) / Q1    → 24
24  if (zeta < options.q_tolerance && summary.num_iterations >= options.min_num_iterations)   đúng → 25   sai → 26
25  summary.termination_type = LinearSolverTerminationType::SUCCESS
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    summary.message = StringPrintf("Iteration: %d Convergence: zeta = %e < %e. |r| = %e", summary.num_iterations, zeta, options.q_tolerance, Norm(r, options.context, options.num_threads))
    break                                                          → END
26  Q0 = Q1
    norm_r = Norm(r, options.context, options.num_threads)         → 27
27  if (norm_r <= tol_r && summary.num_iterations >= options.min_num_iterations)   đúng → 28   sai → 29
28  summary.termination_type = LinearSolverTerminationType::SUCCESS
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    summary.message = StringPrintf("Iteration: %d Convergence. |r| = %e <= %e.", summary.num_iterations, norm_r, tol_r)
    break                                                          → END
29  if (summary.num_iterations >= options.max_num_iterations)      đúng → 30   sai → 31
30  break                                                          → END
31  ++summary.num_iterations                                       → 8
32  Axpby(1., r, -alpha, q, r, options.context, options.num_threads)   → 23
33  const double beta = rho / last_rho                             → 34
34  if (IsZeroOrInfinity(beta))                                    đúng → 35   sai → 36
35  summary.termination_type = LinearSolverTerminationType::FAILURE
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    summary.message = StringPrintf("Numerical failure. beta = rho_n / rho_{n-1} = %e, rho_n = %e, rho_{n-1} = %e", beta, rho, last_rho)
    break                                                          → END
36  Axpby(1., z, beta, p, p, options.context, options.num_threads)   → 14
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
#include "ceres/conjugate_gradients_solver.h"
#include "ceres/linear_solver.h"
```

- Đây là template (khuôn mẫu): khi tạo object hoặc gọi hàm phải chọn kiểu cụ thể phù hợp.

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1369_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
