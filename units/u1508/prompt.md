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

- Hàm: `TrustRegionOptionsAreValid(const Solver::Options & options, std::string * error)`, trả về `bool`
- Loại: hàm tự do (không thuộc class)
- Namespace: `ceres::(namespace không tên)`
- Vị trí: `internal/ceres/solver.cc`, dòng 389–436

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
389 | bool TrustRegionOptionsAreValid(const Solver::Options& options,
390 |                                 std::string* error) {
391 |   OPTION_GT(initial_trust_region_radius, 0.0);
392 |   OPTION_GT(min_trust_region_radius, 0.0);
393 |   OPTION_GT(max_trust_region_radius, 0.0);
394 |   OPTION_LE_OPTION(min_trust_region_radius, max_trust_region_radius);
395 |   OPTION_LE_OPTION(min_trust_region_radius, initial_trust_region_radius);
396 |   OPTION_LE_OPTION(initial_trust_region_radius, max_trust_region_radius);
397 |   OPTION_GE(min_relative_decrease, 0.0);
398 |   OPTION_GE(min_lm_diagonal, 0.0);
399 |   OPTION_GE(max_lm_diagonal, 0.0);
400 |   OPTION_LE_OPTION(min_lm_diagonal, max_lm_diagonal);
401 |   OPTION_GE(max_num_consecutive_invalid_steps, 0);
402 |   OPTION_GT(eta, 0.0);
403 |   OPTION_GE(min_linear_solver_iterations, 0);
404 |   OPTION_GE(max_linear_solver_iterations, 0);
405 |   OPTION_LE_OPTION(min_linear_solver_iterations, max_linear_solver_iterations);
406 | 
407 |   if (options.use_inner_iterations) {
408 |     OPTION_GE(inner_iteration_tolerance, 0.0);
409 |   }
410 | 
411 |   if (options.use_nonmonotonic_steps) {
412 |     OPTION_GT(max_consecutive_nonmonotonic_steps, 0);
413 |   }
414 | 
415 |   if ((options.trust_region_strategy_type == DOGLEG) &&
416 |       IsIterativeSolver(options.linear_solver_type)) {
417 |     *error =
418 |         "DOGLEG only supports exact factorization based linear "
419 |         "solvers. If you want to use an iterative solver please "
420 |         "use LEVENBERG_MARQUARDT as the trust_region_strategy_type";
421 |     return false;
422 |   }
423 | 
424 |   if (!OptionsAreValidForLinearSolver(options, error)) {
425 |     return false;
426 |   }
427 | 
428 |   if (!options.trust_region_minimizer_iterations_to_dump.empty() &&
429 |       options.trust_region_problem_dump_format_type != CONSOLE &&
430 |       options.trust_region_problem_dump_directory.empty()) {
431 |     *error = "Solver::Options::trust_region_problem_dump_directory is empty.";
432 |     return false;
433 |   }
434 | 
435 |   return true;
436 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 22

START → 1
1   if (!(options.initial_trust_region_radius > 0.))               đúng → 2   sai → 3
2   ss << "Invalid configuration. "
    ss << std::string("Solver::Options::initial_trust_region_radius = ") << options.initial_trust_region_radius << ". "
    ss << "Violated constraint: "
    ss << std::string("Solver::Options::initial_trust_region_radius > 0.0")
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = ss.str()
    return false                                                   → END
3   if (!(options.min_trust_region_radius > 0.))                   đúng → 4   sai → 5
4   ss << "Invalid configuration. "
    ss << std::string("Solver::Options::min_trust_region_radius = ") << options.min_trust_region_radius << ". "
    ss << "Violated constraint: "
    ss << std::string("Solver::Options::min_trust_region_radius > 0.0")
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = ss.str()
    return false                                                   → END
5   if (!(options.max_trust_region_radius > 0.))                   đúng → 6   sai → 7
6   ss << "Invalid configuration. "
    ss << std::string("Solver::Options::max_trust_region_radius = ") << options.max_trust_region_radius << ". "
    ss << "Violated constraint: "
    ss << std::string("Solver::Options::max_trust_region_radius > 0.0")
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = ss.str()
    return false                                                   → END
7   if (!(options.min_trust_region_radius <= options.max_trust_region_radius))   đúng → 8   sai → 9
8   ss << "Invalid configuration. "
    ss << std::string("Solver::Options::min_trust_region_radius = ") << options.min_trust_region_radius << ". "
    ss << std::string("Solver::Options::max_trust_region_radius = ") << options.max_trust_region_radius << ". "
    ss << "Violated constraint: "
    ss << std::string("Solver::Options::min_trust_region_radius")
    ss << std::string("<= Solver::Options::max_trust_region_radius.")
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = ss.str()
    return false                                                   → END
9   if (!(options.min_trust_region_radius <= options.initial_trust_region_radius))   đúng → 10   sai → 11
10  ss << "Invalid configuration. "
    ss << std::string("Solver::Options::min_trust_region_radius = ") << options.min_trust_region_radius << ". "
    ss << std::string("Solver::Options::initial_trust_region_radius = ") << options.initial_trust_region_radius << ". "
    ss << "Violated constraint: "
    ss << std::string("Solver::Options::min_trust_region_radius")
    ss << std::string("<= Solver::Options::initial_trust_region_radius.")
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = ss.str()
    return false                                                   → END
11  if (!(options.initial_trust_region_radius <= options.max_trust_region_radius))   đúng → 12   sai → 13
12  ss << "Invalid configuration. "
    ss << std::string("Solver::Options::initial_trust_region_radius = ") << options.initial_trust_region_radius << ". "
    ss << std::string("Solver::Options::max_trust_region_radius = ") << options.max_trust_region_radius << ". "
    ss << "Violated constraint: "
    ss << std::string("Solver::Options::initial_trust_region_radius")
    ss << std::string("<= Solver::Options::max_trust_region_radius.")
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = ss.str()
    return false                                                   → END
13  if (!(options.min_relative_decrease >= 0.))                    đúng → 14   sai → 15
14  ss << "Invalid configuration. "
    ss << std::string("Solver::Options::min_relative_decrease = ") << options.min_relative_decrease << ". "
    ss << "Violated constraint: "
    ss << std::string("Solver::Options::min_relative_decrease >= 0.0")
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = ss.str()
    return false                                                   → END
15  if (!(options.min_lm_diagonal >= 0.))                          đúng → 16   sai → 17
16  ss << "Invalid configuration. "
    ss << std::string("Solver::Options::min_lm_diagonal = ") << options.min_lm_diagonal << ". "
    ss << "Violated constraint: "
    ss << std::string("Solver::Options::min_lm_diagonal >= 0.0")
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = ss.str()
    return false                                                   → END
17  if (!(options.max_lm_diagonal >= 0.))                          đúng → 18   sai → 19
18  ss << "Invalid configuration. "
    ss << std::string("Solver::Options::max_lm_diagonal = ") << options.max_lm_diagonal << ". "
    ss << "Violated constraint: "
    ss << std::string("Solver::Options::max_lm_diagonal >= 0.0")
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = ss.str()
    return false                                                   → END
19  if (!(options.min_lm_diagonal <= options.max_lm_diagonal))     đúng → 20   sai → 21
20  ss << "Invalid configuration. "
    ss << std::string("Solver::Options::min_lm_diagonal = ") << options.min_lm_diagonal << ". "
    ss << std::string("Solver::Options::max_lm_diagonal = ") << options.max_lm_diagonal << ". "
    ss << "Violated constraint: "
    ss << std::string("Solver::Options::min_lm_diagonal")
    ss << std::string("<= Solver::Options::max_lm_diagonal.")
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = ss.str()
    return false                                                   → END
21  if (!(options.max_num_consecutive_invalid_steps >= 0))         đúng → 22   sai → 23
22  ss << "Invalid configuration. "
    ss << std::string("Solver::Options::max_num_consecutive_invalid_steps = ") << options.max_num_consecutive_invalid_steps << ". "
    ss << "Violated constraint: "
    ss << std::string("Solver::Options::max_num_consecutive_invalid_steps >= 0")
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = ss.str()
    return false                                                   → END
23  if (!(options.eta > 0.))                                       đúng → 24   sai → 25
24  ss << "Invalid configuration. "
    ss << std::string("Solver::Options::eta = ") << options.eta << ". "
    ss << "Violated constraint: "
    ss << std::string("Solver::Options::eta > 0.0")
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = ss.str()
    return false                                                   → END
25  if (!(options.min_linear_solver_iterations >= 0))              đúng → 26   sai → 27
26  ss << "Invalid configuration. "
    ss << std::string("Solver::Options::min_linear_solver_iterations = ") << options.min_linear_solver_iterations << ". "
    ss << "Violated constraint: "
    ss << std::string("Solver::Options::min_linear_solver_iterations >= 0")
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = ss.str()
    return false                                                   → END
27  if (!(options.max_linear_solver_iterations >= 0))              đúng → 28   sai → 29
28  ss << "Invalid configuration. "
    ss << std::string("Solver::Options::max_linear_solver_iterations = ") << options.max_linear_solver_iterations << ". "
    ss << "Violated constraint: "
    ss << std::string("Solver::Options::max_linear_solver_iterations >= 0")
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = ss.str()
    return false                                                   → END
29  if (!(options.min_linear_solver_iterations <= options.max_linear_solver_iterations))   đúng → 30   sai → 31
30  ss << "Invalid configuration. "
    ss << std::string("Solver::Options::min_linear_solver_iterations = ") << options.min_linear_solver_iterations << ". "
    ss << std::string("Solver::Options::max_linear_solver_iterations = ") << options.max_linear_solver_iterations << ". "
    ss << "Violated constraint: "
    ss << std::string("Solver::Options::min_linear_solver_iterations")
    ss << std::string("<= Solver::Options::max_linear_solver_iterations.")
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = ss.str()
    return false                                                   → END
31  if (options.use_inner_iterations)                              đúng → 32   sai → 34
32  if (!(options.inner_iteration_tolerance >= 0.))                đúng → 33   sai → 34
33  ss << "Invalid configuration. "
    ss << std::string("Solver::Options::inner_iteration_tolerance = ") << options.inner_iteration_tolerance << ". "
    ss << "Violated constraint: "
    ss << std::string("Solver::Options::inner_iteration_tolerance >= 0.0")
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = ss.str()
    return false                                                   → END
34  if (options.use_nonmonotonic_steps)                            đúng → 35   sai → 37
35  if (!(options.max_consecutive_nonmonotonic_steps > 0))         đúng → 36   sai → 37
36  ss << "Invalid configuration. "
    ss << std::string("Solver::Options::max_consecutive_nonmonotonic_steps = ") << options.max_consecutive_nonmonotonic_steps << ". "
    ss << "Violated constraint: "
    ss << std::string("Solver::Options::max_consecutive_nonmonotonic_steps > 0")
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = ss.str()
    return false                                                   → END
37  if (options.trust_region_strategy_type == DOGLEG) && IsIterativeSolver(options.linear_solver_type)   đúng → 38   sai → 39
38  *error = "DOGLEG only supports exact factorization based linear solvers. If you want to use an iterative solver please use LEVENBERG_MARQUARDT as the trust_region_strategy_type"
    return false                                                   → END
39  if (!OptionsAreValidForLinearSolver(options, error))           đúng → 40   sai → 41
40  return false                                                   → END
41  if (!options.trust_region_minimizer_iterations_to_dump.empty() && options.trust_region_problem_dump_format_type != CONSOLE && options.trust_region_problem_dump_directory.empty())   đúng → 42   sai → 43
42  *error = "Solver::Options::trust_region_problem_dump_directory is empty."
    return false                                                   → END
43  return true                                                    → END
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
#include "ceres/solver.cc"
```

- Hàm này chỉ dùng được bên trong file `internal/ceres/solver.cc` (khai báo `static` hoặc trong namespace không tên). Để gọi được, thêm `#include "ceres/solver.cc"` vào file test.

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1508_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
