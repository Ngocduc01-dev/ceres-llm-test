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

- Hàm: `Minimize(const Minimizer::Options & options, double * parameters, Solver::Summary * summary)`, trả về `void`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::LineSearchMinimizer`
- Vị trí: `internal/ceres/line_search_minimizer.cc`, dòng 85–473

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
 85 | void LineSearchMinimizer::Minimize(const Minimizer::Options& options,
 86 |                                    double* parameters,
 87 |                                    Solver::Summary* summary) {
 88 |   const bool is_not_silent = !options.is_silent;
 89 |   double start_time = WallTimeInSeconds();
 90 |   double iteration_start_time = start_time;
 91 | 
 92 |   CHECK(options.evaluator != nullptr);
 93 |   Evaluator* evaluator = options.evaluator.get();
 94 |   const int num_parameters = evaluator->NumParameters();
 95 |   const int num_effective_parameters = evaluator->NumEffectiveParameters();
 96 | 
 97 |   summary->termination_type = NO_CONVERGENCE;
 98 |   summary->num_successful_steps = 0;
 99 |   summary->num_unsuccessful_steps = 0;
100 | 
101 |   VectorRef x(parameters, num_parameters);
102 | 
103 |   State current_state(num_parameters, num_effective_parameters);
104 |   State previous_state(num_parameters, num_effective_parameters);
105 | 
106 |   IterationSummary iteration_summary;
107 |   iteration_summary.iteration = 0;
108 |   iteration_summary.step_is_valid = false;
109 |   iteration_summary.step_is_successful = false;
110 |   iteration_summary.cost_change = 0.0;
111 |   iteration_summary.gradient_max_norm = 0.0;
112 |   iteration_summary.gradient_norm = 0.0;
113 |   iteration_summary.step_norm = 0.0;
114 |   iteration_summary.linear_solver_iterations = 0;
115 |   iteration_summary.step_solver_time_in_seconds = 0;
116 | 
117 |   // Do initial cost and gradient evaluation.
118 |   if (!evaluator->Evaluate(x.data(),
119 |                            &(current_state.cost),
120 |                            nullptr,
121 |                            current_state.gradient.data(),
122 |                            nullptr)) {
123 |     summary->termination_type = FAILURE;
124 |     summary->message = "Initial cost and jacobian evaluation failed.";
125 |     if (is_not_silent) {
126 |       LOG(WARNING) << "Terminating: " << summary->message;
127 |     }
128 |     return;
129 |   }
130 | 
131 |   if (!EvaluateGradientNorms(evaluator, x, &current_state, &summary->message)) {
132 |     summary->termination_type = FAILURE;
133 |     summary->message =
134 |         "Initial cost and jacobian evaluation failed. More details: " +
135 |         summary->message;
136 |     if (is_not_silent) {
137 |       LOG(WARNING) << "Terminating: " << summary->message;
138 |     }
139 |     return;
140 |   }
141 | 
142 |   summary->initial_cost = current_state.cost + summary->fixed_cost;
143 |   iteration_summary.cost = current_state.cost + summary->fixed_cost;
144 | 
145 |   iteration_summary.gradient_norm = sqrt(current_state.gradient_squared_norm);
146 |   iteration_summary.gradient_max_norm = current_state.gradient_max_norm;
147 |   if (iteration_summary.gradient_max_norm <= options.gradient_tolerance) {
148 |     summary->message =
149 |         StringPrintf("Gradient tolerance reached. Gradient max norm: %e <= %e",
150 |                      iteration_summary.gradient_max_norm,
151 |                      options.gradient_tolerance);
152 |     summary->termination_type = CONVERGENCE;
153 |     if (is_not_silent) {
154 |       VLOG(1) << "Terminating: " << summary->message;
155 |     }
156 |     return;
157 |   }
158 | 
159 |   iteration_summary.iteration_time_in_seconds =
160 |       WallTimeInSeconds() - iteration_start_time;
161 |   iteration_summary.cumulative_time_in_seconds =
162 |       WallTimeInSeconds() - start_time + summary->preprocessor_time_in_seconds;
163 |   summary->iterations.push_back(iteration_summary);
164 | 
165 |   LineSearchDirection::Options line_search_direction_options;
166 |   line_search_direction_options.num_parameters = num_effective_parameters;
167 |   line_search_direction_options.type = options.line_search_direction_type;
168 |   line_search_direction_options.nonlinear_conjugate_gradient_type =
169 |       options.nonlinear_conjugate_gradient_type;
170 |   line_search_direction_options.max_lbfgs_rank = options.max_lbfgs_rank;
171 |   line_search_direction_options.use_approximate_eigenvalue_bfgs_scaling =
172 |       options.use_approximate_eigenvalue_bfgs_scaling;
173 |   std::unique_ptr<LineSearchDirection> line_search_direction =
174 |       LineSearchDirection::Create(line_search_direction_options);
175 | 
176 |   LineSearchFunction line_search_function(evaluator);
177 | 
178 |   LineSearch::Options line_search_options;
179 |   line_search_options.interpolation_type =
180 |       options.line_search_interpolation_type;
181 |   line_search_options.min_step_size = options.min_line_search_step_size;
182 |   line_search_options.sufficient_decrease =
183 |       options.line_search_sufficient_function_decrease;
184 |   line_search_options.max_step_contraction =
185 |       options.max_line_search_step_contraction;
186 |   line_search_options.min_step_contraction =
187 |       options.min_line_search_step_contraction;
188 |   line_search_options.max_num_iterations =
189 |       options.max_num_line_search_step_size_iterations;
190 |   line_search_options.sufficient_curvature_decrease =
191 |       options.line_search_sufficient_curvature_decrease;
192 |   line_search_options.max_step_expansion =
193 |       options.max_line_search_step_expansion;
194 |   line_search_options.is_silent = options.is_silent;
195 |   line_search_options.function = &line_search_function;
196 | 
197 |   std::unique_ptr<LineSearch> line_search(LineSearch::Create(
198 |       options.line_search_type, line_search_options, &summary->message));
199 |   if (line_search.get() == nullptr) {
200 |     summary->termination_type = FAILURE;
201 |     if (is_not_silent) {
202 |       LOG(ERROR) << "Terminating: " << summary->message;
203 |     }
204 |     return;
205 |   }
206 | 
207 |   LineSearch::Summary line_search_summary;
208 |   int num_line_search_direction_restarts = 0;
209 | 
210 |   while (true) {
211 |     if (!RunCallbacks(options, iteration_summary, summary)) {
212 |       break;
213 |     }
214 | 
215 |     iteration_start_time = WallTimeInSeconds();
216 |     if (iteration_summary.iteration >= options.max_num_iterations) {
217 |       summary->message = "Maximum number of iterations reached.";
218 |       summary->termination_type = NO_CONVERGENCE;
219 |       if (is_not_silent) {
220 |         VLOG(1) << "Terminating: " << summary->message;
221 |       }
222 |       break;
223 |     }
224 | 
225 |     const double total_solver_time = iteration_start_time - start_time +
226 |                                      summary->preprocessor_time_in_seconds;
227 |     if (total_solver_time >= options.max_solver_time_in_seconds) {
228 |       summary->message = "Maximum solver time reached.";
229 |       summary->termination_type = NO_CONVERGENCE;
230 |       if (is_not_silent) {
231 |         VLOG(1) << "Terminating: " << summary->message;
232 |       }
233 |       break;
234 |     }
235 | 
236 |     iteration_summary = IterationSummary();
237 |     iteration_summary.iteration = summary->iterations.back().iteration + 1;
238 |     iteration_summary.step_is_valid = false;
239 |     iteration_summary.step_is_successful = false;
240 | 
241 |     bool line_search_status = true;
242 |     if (iteration_summary.iteration == 1) {
243 |       current_state.search_direction = -current_state.gradient;
244 |     } else {
245 |       line_search_status = line_search_direction->NextDirection(
246 |           previous_state, current_state, &current_state.search_direction);
247 |     }
248 | 
249 |     if (!line_search_status &&
250 |         num_line_search_direction_restarts >=
251 |             options.max_num_line_search_direction_restarts) {
252 |       // Line search direction failed to generate a new direction, and we
253 |       // have already reached our specified maximum number of restarts,
254 |       // terminate optimization.
255 |       summary->message = StringPrintf(
256 |           "Line search direction failure: specified "
257 |           "max_num_line_search_direction_restarts: %d reached.",
258 |           options.max_num_line_search_direction_restarts);
259 |       summary->termination_type = FAILURE;
260 |       if (is_not_silent) {
261 |         LOG(WARNING) << "Terminating: " << summary->message;
262 |       }
263 |       break;
264 |     } else if (!line_search_status) {
265 |       // Restart line search direction with gradient descent on first iteration
266 |       // as we have not yet reached our maximum number of restarts.
267 |       CHECK_LT(num_line_search_direction_restarts,
268 |                options.max_num_line_search_direction_restarts);
269 | 
270 |       ++num_line_search_direction_restarts;
271 |       if (is_not_silent) {
272 |         LOG(WARNING) << "Line search direction algorithm: "
273 |                      << LineSearchDirectionTypeToString(
274 |                             options.line_search_direction_type)
275 |                      << ", failed to produce a valid new direction at "
276 |                      << "iteration: " << iteration_summary.iteration
277 |                      << ". Restarting, number of restarts: "
278 |                      << num_line_search_direction_restarts << " / "
279 |                      << options.max_num_line_search_direction_restarts
280 |                      << " [max].";
281 |       }
282 |       line_search_direction =
283 |           LineSearchDirection::Create(line_search_direction_options);
284 |       current_state.search_direction = -current_state.gradient;
285 |     }
286 | 
287 |     line_search_function.Init(x, current_state.search_direction);
288 |     current_state.directional_derivative =
289 |         current_state.gradient.dot(current_state.search_direction);
290 | 
291 |     // TODO(sameeragarwal): Refactor this into its own object and add
292 |     // explanations for the various choices.
293 |     //
294 |     // Note that we use !line_search_status to ensure that we treat cases when
295 |     // we restarted the line search direction equivalently to the first
296 |     // iteration.
297 |     const double initial_step_size =
298 |         (iteration_summary.iteration == 1 || !line_search_status)
299 |             ? std::min(1.0, 1.0 / current_state.gradient_max_norm)
300 |             : std::min(1.0,
301 |                        2.0 * (current_state.cost - previous_state.cost) /
302 |                            current_state.directional_derivative);
303 |     // By definition, we should only ever go forwards along the specified search
304 |     // direction in a line search, most likely cause for this being violated
305 |     // would be a numerical failure in the line search direction calculation.
306 |     if (initial_step_size < 0.0) {
307 |       summary->message = StringPrintf(
308 |           "Numerical failure in line search, initial_step_size is "
309 |           "negative: %.5e, directional_derivative: %.5e, "
310 |           "(current_cost - previous_cost): %.5e",
311 |           initial_step_size,
312 |           current_state.directional_derivative,
313 |           (current_state.cost - previous_state.cost));
314 |       summary->termination_type = FAILURE;
315 |       if (is_not_silent) {
316 |         LOG(WARNING) << "Terminating: " << summary->message;
317 |       }
318 |       break;
319 |     }
320 | 
321 |     line_search->Search(initial_step_size,
322 |                         current_state.cost,
323 |                         current_state.directional_derivative,
324 |                         &line_search_summary);
325 |     if (!line_search_summary.success) {
326 |       summary->message = StringPrintf(
327 |           "Numerical failure in line search, failed to find "
328 |           "a valid step size, (did not run out of iterations) "
329 |           "using initial_step_size: %.5e, initial_cost: %.5e, "
330 |           "initial_gradient: %.5e.",
331 |           initial_step_size,
332 |           current_state.cost,
333 |           current_state.directional_derivative);
334 |       if (is_not_silent) {
335 |         LOG(WARNING) << "Terminating: " << summary->message;
336 |       }
337 |       summary->termination_type = FAILURE;
338 |       break;
339 |     }
340 | 
341 |     const FunctionSample& optimal_point = line_search_summary.optimal_point;
342 |     CHECK(optimal_point.vector_x_is_valid)
343 |         << "Congratulations, you found a bug in Ceres. Please report it.";
344 |     current_state.step_size = optimal_point.x;
345 |     previous_state = current_state;
346 |     iteration_summary.step_solver_time_in_seconds =
347 |         WallTimeInSeconds() - iteration_start_time;
348 | 
349 |     if (optimal_point.vector_gradient_is_valid) {
350 |       current_state.cost = optimal_point.value;
351 |       current_state.gradient = optimal_point.vector_gradient;
352 |     } else {
353 |       Evaluator::EvaluateOptions evaluate_options;
354 |       evaluate_options.new_evaluation_point = false;
355 |       if (!evaluator->Evaluate(evaluate_options,
356 |                                optimal_point.vector_x.data(),
357 |                                &(current_state.cost),
358 |                                nullptr,
359 |                                current_state.gradient.data(),
360 |                                nullptr)) {
361 |         summary->termination_type = FAILURE;
362 |         summary->message = "Cost and jacobian evaluation failed.";
363 |         if (is_not_silent) {
364 |           LOG(WARNING) << "Terminating: " << summary->message;
365 |         }
366 |         return;
367 |       }
368 |     }
369 | 
370 |     if (!EvaluateGradientNorms(evaluator,
371 |                                optimal_point.vector_x,
372 |                                &current_state,
373 |                                &summary->message)) {
374 |       summary->termination_type = FAILURE;
375 |       summary->message =
376 |           "Step failed to evaluate. This should not happen as the step was "
377 |           "valid when it was selected by the line search. More details: " +
378 |           summary->message;
379 |       if (is_not_silent) {
380 |         LOG(WARNING) << "Terminating: " << summary->message;
381 |       }
382 |       break;
383 |     }
384 | 
385 |     // Compute the norm of the step in the ambient space.
386 |     iteration_summary.step_norm = (optimal_point.vector_x - x).norm();
387 |     const double x_norm = x.norm();
388 |     x = optimal_point.vector_x;
389 | 
390 |     iteration_summary.gradient_max_norm = current_state.gradient_max_norm;
391 |     iteration_summary.gradient_norm = sqrt(current_state.gradient_squared_norm);
392 |     iteration_summary.cost_change = previous_state.cost - current_state.cost;
393 |     iteration_summary.cost = current_state.cost + summary->fixed_cost;
394 | 
395 |     iteration_summary.step_is_valid = true;
396 |     iteration_summary.step_is_successful = true;
397 |     iteration_summary.step_size = current_state.step_size;
398 |     iteration_summary.line_search_function_evaluations =
399 |         line_search_summary.num_function_evaluations;
400 |     iteration_summary.line_search_gradient_evaluations =
401 |         line_search_summary.num_gradient_evaluations;
402 |     iteration_summary.line_search_iterations =
403 |         line_search_summary.num_iterations;
404 |     iteration_summary.iteration_time_in_seconds =
405 |         WallTimeInSeconds() - iteration_start_time;
406 |     iteration_summary.cumulative_time_in_seconds =
407 |         WallTimeInSeconds() - start_time +
408 |         summary->preprocessor_time_in_seconds;
409 |     summary->iterations.push_back(iteration_summary);
410 | 
411 |     // Iterations inside the line search algorithm are considered
412 |     // 'steps' in the broader context, to distinguish these inner
413 |     // iterations from from the outer iterations of the line search
414 |     // minimizer. The number of line search steps is the total number
415 |     // of inner line search iterations (or steps) across the entire
416 |     // minimization.
417 |     summary->num_line_search_steps += line_search_summary.num_iterations;
418 |     summary->line_search_cost_evaluation_time_in_seconds +=
419 |         line_search_summary.cost_evaluation_time_in_seconds;
420 |     summary->line_search_gradient_evaluation_time_in_seconds +=
421 |         line_search_summary.gradient_evaluation_time_in_seconds;
422 |     summary->line_search_polynomial_minimization_time_in_seconds +=
423 |         line_search_summary.polynomial_minimization_time_in_seconds;
424 |     summary->line_search_total_time_in_seconds +=
425 |         line_search_summary.total_time_in_seconds;
426 |     ++summary->num_successful_steps;
427 | 
428 |     const double step_size_tolerance =
429 |         options.parameter_tolerance * (x_norm + options.parameter_tolerance);
430 |     if (iteration_summary.step_norm <= step_size_tolerance) {
431 |       summary->message = StringPrintf(
432 |           "Parameter tolerance reached. "
433 |           "Relative step_norm: %e <= %e.",
434 |           (iteration_summary.step_norm /
435 |            (x_norm + options.parameter_tolerance)),
436 |           options.parameter_tolerance);
437 |       summary->termination_type = CONVERGENCE;
438 |       if (is_not_silent) {
439 |         VLOG(1) << "Terminating: " << summary->message;
440 |       }
441 |       return;
442 |     }
443 | 
444 |     if (iteration_summary.gradient_max_norm <= options.gradient_tolerance) {
445 |       summary->message = StringPrintf(
446 |           "Gradient tolerance reached. "
447 |           "Gradient max norm: %e <= %e",
448 |           iteration_summary.gradient_max_norm,
449 |           options.gradient_tolerance);
450 |       summary->termination_type = CONVERGENCE;
451 |       if (is_not_silent) {
452 |         VLOG(1) << "Terminating: " << summary->message;
453 |       }
454 |       break;
455 |     }
456 | 
457 |     const double absolute_function_tolerance =
458 |         options.function_tolerance * std::abs(previous_state.cost);
459 |     if (std::abs(iteration_summary.cost_change) <=
460 |         absolute_function_tolerance) {
461 |       summary->message = StringPrintf(
462 |           "Function tolerance reached. "
463 |           "|cost_change|/cost: %e <= %e",
464 |           std::abs(iteration_summary.cost_change) / previous_state.cost,
465 |           options.function_tolerance);
466 |       summary->termination_type = CONVERGENCE;
467 |       if (is_not_silent) {
468 |         VLOG(1) << "Terminating: " << summary->message;
469 |       }
470 |       break;
471 |     }
472 |   }
473 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 34 (và 3 lệnh CHECK)

START → 1
1   const bool is_not_silent = !options.is_silent
    double start_time = WallTimeInSeconds()
    double iteration_start_time = start_time                       → 2
2   CHECK(options.evaluator != nullptr)                            đúng → 3   sai → DỪNG
3   Evaluator *evaluator = options.evaluator.get()
    const int num_parameters = evaluator->NumParameters()
    const int num_effective_parameters = evaluator->NumEffectiveParameters()
    summary->termination_type = NO_CONVERGENCE
    summary->num_successful_steps = 0
    summary->num_unsuccessful_steps = 0
    parameters, num_parameters
    num_parameters, num_effective_parameters
    num_parameters, num_effective_parameters
    iteration_summary.iteration = 0
    iteration_summary.step_is_valid = false
    iteration_summary.step_is_successful = false
    iteration_summary.cost_change = 0.
    iteration_summary.gradient_max_norm = 0.
    iteration_summary.gradient_norm = 0.
    iteration_summary.step_norm = 0.
    iteration_summary.linear_solver_iterations = 0
    iteration_summary.step_solver_time_in_seconds = 0              → 4
4   if (!evaluator->Evaluate(x.data(), &(current_state.cost), nullptr, current_state.gradient.data(), nullptr))   đúng → 5   sai → 8
5   summary->termination_type = FAILURE
    summary->message = "Initial cost and jacobian evaluation failed."   → 6
6   if (is_not_silent)                                             đúng → 7   sai → 7
7   return                                                         → END
8   if (!EvaluateGradientNorms(evaluator, x, &current_state, &summary->message))   đúng → 9   sai → 12
9   summary->termination_type = FAILURE
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    summary->message = "Initial cost and jacobian evaluation failed. More details: " + summary->message   → 10
10  if (is_not_silent)                                             đúng → 11   sai → 11
11  return                                                         → END
12  summary->initial_cost = current_state.cost + summary->fixed_cost
    iteration_summary.cost = current_state.cost + summary->fixed_cost
    iteration_summary.gradient_norm = sqrt(current_state.gradient_squared_norm)
    iteration_summary.gradient_max_norm = current_state.gradient_max_norm   → 13
13  if (iteration_summary.gradient_max_norm <= options.gradient_tolerance)   đúng → 14   sai → 17
14  operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    summary->message = StringPrintf("Gradient tolerance reached. Gradient max norm: %e <= %e", iteration_summary.gradient_max_norm, options.gradient_tolerance)
    summary->termination_type = CONVERGENCE                        → 15
15  if (is_not_silent)                                             đúng → 16   sai → 16
16  return                                                         → END
17  iteration_summary.iteration_time_in_seconds = WallTimeInSeconds() - iteration_start_time
    iteration_summary.cumulative_time_in_seconds = WallTimeInSeconds() - start_time + summary->preprocessor_time_in_seconds
    summary->iterations.push_back(iteration_summary)
    line_search_direction_options.num_parameters = num_effective_parameters
    line_search_direction_options.type = options.line_search_direction_type
    line_search_direction_options.nonlinear_conjugate_gradient_type = options.nonlinear_conjugate_gradient_type
    line_search_direction_options.max_lbfgs_rank = options.max_lbfgs_rank
    line_search_direction_options.use_approximate_eigenvalue_bfgs_scaling = options.use_approximate_eigenvalue_bfgs_scaling
    line_search_options.interpolation_type = options.line_search_interpolation_type
    line_search_options.min_step_size = options.min_line_search_step_size
    line_search_options.sufficient_decrease = options.line_search_sufficient_function_decrease
    line_search_options.max_step_contraction = options.max_line_search_step_contraction
    line_search_options.min_step_contraction = options.min_line_search_step_contraction
    line_search_options.max_num_iterations = options.max_num_line_search_step_size_iterations
    line_search_options.sufficient_curvature_decrease = options.line_search_sufficient_curvature_decrease
    line_search_options.max_step_expansion = options.max_line_search_step_expansion
    line_search_options.is_silent = options.is_silent
    line_search_options.function = &line_search_function           → 18
18  if (line_search.get() == nullptr)                              đúng → 19   sai → 22
19  summary->termination_type = FAILURE                            → 20
20  if (is_not_silent)                                             đúng → 21   sai → 21
21  return                                                         → END
22  int num_line_search_direction_restarts = 0                     → 23
23  while true                                                     → 24
24  if (!RunCallbacks(options, iteration_summary, summary))        đúng → 25   sai → 26
25  break                                                          → END
26  iteration_start_time = WallTimeInSeconds()                     → 27
27  if (iteration_summary.iteration >= options.max_num_iterations)   đúng → 28   sai → 31
28  summary->message = "Maximum number of iterations reached."
    summary->termination_type = NO_CONVERGENCE                     → 29
29  if (is_not_silent)                                             đúng → 30   sai → 30
30  break                                                          → END
31  const double total_solver_time = iteration_start_time - start_time + summary->preprocessor_time_in_seconds   → 32
32  if (total_solver_time >= options.max_solver_time_in_seconds)   đúng → 33   sai → 36
33  summary->message = "Maximum solver time reached."
    summary->termination_type = NO_CONVERGENCE                     → 34
34  if (is_not_silent)                                             đúng → 35   sai → 35
35  break                                                          → END
36  iteration_summary = IterationSummary()
    iteration_summary.iteration = summary->iterations.back().iteration + 1
    iteration_summary.step_is_valid = false
    iteration_summary.step_is_successful = false
    bool line_search_status = true                                 → 37
37  if (iteration_summary.iteration == 1)                          đúng → 38   sai → 88
38  current_state.search_direction = - current_state.gradient      → 39
39  if (!line_search_status && num_line_search_direction_restarts >= options.max_num_line_search_direction_restarts)   đúng → 40   sai → 43
40  operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    summary->message = StringPrintf("Line search direction failure: specified max_num_line_search_direction_restarts: %d reached.", options.max_num_line_search_direction_restarts)
    summary->termination_type = FAILURE                            → 41
41  if (is_not_silent)                                             đúng → 42   sai → 42
42  break                                                          → END
43  if (!line_search_status)                                       đúng → 44   sai → 48
44  options.max_num_line_search_direction_restarts)                đúng → 45   sai → DỪNG
45  ++num_line_search_direction_restarts                           → 46
46  if (is_not_silent)                                             đúng → 47   sai → 47
47  line_search_direction = LineSearchDirection::Create(line_search_direction_options)
    current_state.search_direction = - current_state.gradient      → 48
48  line_search_function.Init(x, current_state.search_direction)
    current_state.directional_derivative = current_state.gradient.dot(current_state.search_direction)   → 49
49  (iteration_summary.iteration == 1 || !line_search_status) ? ... : ...   đúng → 50   sai → 50
50  const double initial_step_size = (iteration_summary.iteration == 1 || !line_search_status) ? std::min(1., 1. / current_state.gradient_max_norm) : std::min(1., 2. * (current_state.cost - previous_state.cost) / current_state.directional_derivative)   → 51
51  if (initial_step_size < 0.)                                    đúng → 52   sai → 55
52  operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    summary->message = StringPrintf("Numerical failure in line search, initial_step_size is negative: %.5e, directional_derivative: %.5e, (current_cost - previous_cost): %.5e", initial_step_size, current_state.directional_derivative, (current_state.cost - previous_state.cost))
    summary->termination_type = FAILURE                            → 53
53  if (is_not_silent)                                             đúng → 54   sai → 54
54  break                                                          → END
55  line_search->Search(initial_step_size, current_state.cost, current_state.directional_derivative, &line_search_summary)   → 56
56  if (!line_search_summary.success)                              đúng → 57   sai → 60
57  operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    summary->message = StringPrintf("Numerical failure in line search, failed to find a valid step size, (did not run out of iterations) using initial_step_size: %.5e, initial_cost: %.5e, initial_gradient: %.5e.", initial_step_size, current_state.cost, current_state.directional_derivative)   → 58
58  if (is_not_silent)                                             đúng → 59   sai → 59
59  summary->termination_type = FAILURE
    break                                                          → END
60  const FunctionSample &optimal_point = line_search_summary.optimal_point   → 61
61  CHECK(optimal_point.vector_x_is_valid)                         đúng → 62   sai → DỪNG
62  current_state.step_size = optimal_point.x
    previous_state = current_state
    iteration_summary.step_solver_time_in_seconds = WallTimeInSeconds() - iteration_start_time   → 63
63  if (optimal_point.vector_gradient_is_valid)                    đúng → 64   sai → 83
64  current_state.cost = optimal_point.value
    current_state.gradient = optimal_point.vector_gradient         → 65
65  if (!EvaluateGradientNorms(evaluator, optimal_point.vector_x, &current_state, &summary->message))   đúng → 66   sai → 69
66  summary->termination_type = FAILURE
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    summary->message = "Step failed to evaluate. This should not happen as the step was valid when it was selected by the line search. More details: " + summary->message   → 67
67  if (is_not_silent)                                             đúng → 68   sai → 68
68  break                                                          → END
69  iteration_summary.step_norm = (optimal_point.vector_x - x).norm()
    const double x_norm = x.norm()
    x = optimal_point.vector_x
    iteration_summary.gradient_max_norm = current_state.gradient_max_norm
    iteration_summary.gradient_norm = sqrt(current_state.gradient_squared_norm)
    iteration_summary.cost_change = previous_state.cost - current_state.cost
    iteration_summary.cost = current_state.cost + summary->fixed_cost
    iteration_summary.step_is_valid = true
    iteration_summary.step_is_successful = true
    iteration_summary.step_size = current_state.step_size
    iteration_summary.line_search_function_evaluations = line_search_summary.num_function_evaluations
    iteration_summary.line_search_gradient_evaluations = line_search_summary.num_gradient_evaluations
    iteration_summary.line_search_iterations = line_search_summary.num_iterations
    iteration_summary.iteration_time_in_seconds = WallTimeInSeconds() - iteration_start_time
    iteration_summary.cumulative_time_in_seconds = WallTimeInSeconds() - start_time + summary->preprocessor_time_in_seconds
    summary->iterations.push_back(iteration_summary)
    summary->num_line_search_steps += line_search_summary.num_iterations
    summary->line_search_cost_evaluation_time_in_seconds += line_search_summary.cost_evaluation_time_in_seconds
    summary->line_search_gradient_evaluation_time_in_seconds += line_search_summary.gradient_evaluation_time_in_seconds
    summary->line_search_polynomial_minimization_time_in_seconds += line_search_summary.polynomial_minimization_time_in_seconds
    summary->line_search_total_time_in_seconds += line_search_summary.total_time_in_seconds
    ++summary->num_successful_steps
    const double step_size_tolerance = options.parameter_tolerance * (x_norm + options.parameter_tolerance)   → 70
70  if (iteration_summary.step_norm <= step_size_tolerance)        đúng → 71   sai → 74
71  operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    summary->message = StringPrintf("Parameter tolerance reached. Relative step_norm: %e <= %e.", (iteration_summary.step_norm / (x_norm + options.parameter_tolerance)), options.parameter_tolerance)
    summary->termination_type = CONVERGENCE                        → 72
72  if (is_not_silent)                                             đúng → 73   sai → 73
73  return                                                         → END
74  if (iteration_summary.gradient_max_norm <= options.gradient_tolerance)   đúng → 75   sai → 78
75  operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    summary->message = StringPrintf("Gradient tolerance reached. Gradient max norm: %e <= %e", iteration_summary.gradient_max_norm, options.gradient_tolerance)
    summary->termination_type = CONVERGENCE                        → 76
76  if (is_not_silent)                                             đúng → 77   sai → 77
77  break                                                          → END
78  const double absolute_function_tolerance = options.function_tolerance * std::abs(previous_state.cost)   → 79
79  if (std::abs(iteration_summary.cost_change) <= absolute_function_tolerance)   đúng → 80   sai → 23
80  operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    summary->message = StringPrintf("Function tolerance reached. |cost_change|/cost: %e <= %e", std::abs(iteration_summary.cost_change) / previous_state.cost, options.function_tolerance)
    summary->termination_type = CONVERGENCE                        → 81
81  if (is_not_silent)                                             đúng → 82   sai → 82
82  break                                                          → END
83  evaluate_options.new_evaluation_point = false                  → 84
84  if (!evaluator->Evaluate(evaluate_options, optimal_point.vector_x.data(), &(current_state.cost), nullptr, current_state.gradient.data(), nullptr))   đúng → 85   sai → 65
85  summary->termination_type = FAILURE
    summary->message = "Cost and jacobian evaluation failed."      → 86
86  if (is_not_silent)                                             đúng → 87   sai → 87
87  return                                                         → END
88  line_search_status = line_search_direction->NextDirection(previous_state, current_state, &current_state.search_direction)   → 39
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
#include "ceres/iteration_callback.h"
#include "ceres/solver.h"
#include "ceres/evaluator.h"
#include "ceres/function_sample.h"
#include "ceres/line_search.h"
#include "ceres/line_search_direction.h"
#include "ceres/line_search_minimizer.h"
#include "ceres/minimizer.h"
```

- Đây là method của class `ceres::internal::LineSearchMinimizer`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `LineSearchMinimizer`:
- Class không tự khai báo constructor → tạo bằng constructor mặc định: `LineSearchMinimizer obj;`

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1447_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
