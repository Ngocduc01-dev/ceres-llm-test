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

- Hàm: `LineSearchOptionsAreValid(const Solver::Options & options, std::string * error)`, trả về `bool`
- Loại: hàm tự do (không thuộc class)
- Namespace: `ceres::(namespace không tên)`
- Vị trí: `internal/ceres/solver.cc`, dòng 438–485

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
438 | bool LineSearchOptionsAreValid(const Solver::Options& options,
439 |                                std::string* error) {
440 |   OPTION_GT(max_lbfgs_rank, 0);
441 |   OPTION_GT(min_line_search_step_size, 0.0);
442 |   OPTION_GT(max_line_search_step_contraction, 0.0);
443 |   OPTION_LT(max_line_search_step_contraction, 1.0);
444 |   OPTION_LT_OPTION(max_line_search_step_contraction,
445 |                    min_line_search_step_contraction);
446 |   OPTION_LE(min_line_search_step_contraction, 1.0);
447 |   OPTION_GE(max_num_line_search_step_size_iterations,
448 |             (options.minimizer_type == ceres::TRUST_REGION ? 0 : 1));
449 |   OPTION_GT(line_search_sufficient_function_decrease, 0.0);
450 |   OPTION_LT_OPTION(line_search_sufficient_function_decrease,
451 |                    line_search_sufficient_curvature_decrease);
452 |   OPTION_LT(line_search_sufficient_curvature_decrease, 1.0);
453 |   OPTION_GT(max_line_search_step_expansion, 1.0);
454 | 
455 |   if ((options.line_search_direction_type == ceres::BFGS ||
456 |        options.line_search_direction_type == ceres::LBFGS) &&
457 |       options.line_search_type != ceres::WOLFE) {
458 |     *error =
459 |         std::string(
460 |             "Invalid configuration: Solver::Options::line_search_type = ") +
461 |         std::string(LineSearchTypeToString(options.line_search_type)) +
462 |         std::string(
463 |             ". When using (L)BFGS, "
464 |             "Solver::Options::line_search_type must be set to WOLFE.");
465 |     return false;
466 |   }
467 | 
468 |   // Warn user if they have requested BISECTION interpolation, but constraints
469 |   // on max/min step size change during line search prevent bisection scaling
470 |   // from occurring. Warn only, as this is likely a user mistake, but one
471 |   // which does not prevent us from continuing.
472 |   if (options.line_search_interpolation_type == ceres::BISECTION &&
473 |       (options.max_line_search_step_contraction > 0.5 ||
474 |        options.min_line_search_step_contraction < 0.5)) {
475 |     LOG(WARNING)
476 |         << "Line search interpolation type is BISECTION, but specified "
477 |         << "max_line_search_step_contraction: "
478 |         << options.max_line_search_step_contraction << ", and "
479 |         << "min_line_search_step_contraction: "
480 |         << options.min_line_search_step_contraction
481 |         << ", prevent bisection (0.5) scaling, continuing with solve "
482 |            "regardless.";
483 |   }
484 |   return true;
485 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 14

START → 1
1   if (!(options.max_lbfgs_rank > 0))                             đúng → 2   sai → 3
2   ss << "Invalid configuration. "
    ss << std::string("Solver::Options::max_lbfgs_rank = ") << options.max_lbfgs_rank << ". "
    ss << "Violated constraint: "
    ss << std::string("Solver::Options::max_lbfgs_rank > 0")
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = ss.str()
    return false                                                   → END
3   if (!(options.min_line_search_step_size > 0.))                 đúng → 4   sai → 5
4   ss << "Invalid configuration. "
    ss << std::string("Solver::Options::min_line_search_step_size = ") << options.min_line_search_step_size << ". "
    ss << "Violated constraint: "
    ss << std::string("Solver::Options::min_line_search_step_size > 0.0")
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = ss.str()
    return false                                                   → END
5   if (!(options.max_line_search_step_contraction > 0.))          đúng → 6   sai → 7
6   ss << "Invalid configuration. "
    ss << std::string("Solver::Options::max_line_search_step_contraction = ") << options.max_line_search_step_contraction << ". "
    ss << "Violated constraint: "
    ss << std::string("Solver::Options::max_line_search_step_contraction > 0.0")
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = ss.str()
    return false                                                   → END
7   if (!(options.max_line_search_step_contraction < 1.))          đúng → 8   sai → 9
8   ss << "Invalid configuration. "
    ss << std::string("Solver::Options::max_line_search_step_contraction = ") << options.max_line_search_step_contraction << ". "
    ss << "Violated constraint: "
    ss << std::string("Solver::Options::max_line_search_step_contraction < 1.0")
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = ss.str()
    return false                                                   → END
9   if (!(options.max_line_search_step_contraction < options.min_line_search_step_contraction))   đúng → 10   sai → 11
10  ss << "Invalid configuration. "
    ss << std::string("Solver::Options::max_line_search_step_contraction = ") << options.max_line_search_step_contraction << ". "
    ss << std::string("Solver::Options::min_line_search_step_contraction = ") << options.min_line_search_step_contraction << ". "
    ss << "Violated constraint: "
    ss << std::string("Solver::Options::max_line_search_step_contraction")
    ss << std::string("< Solver::Options::min_line_search_step_contraction.")
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = ss.str()
    return false                                                   → END
11  if (!(options.min_line_search_step_contraction <= 1.))         đúng → 12   sai → 13
12  ss << "Invalid configuration. "
    ss << std::string("Solver::Options::min_line_search_step_contraction = ") << options.min_line_search_step_contraction << ". "
    ss << "Violated constraint: "
    ss << std::string("Solver::Options::min_line_search_step_contraction <= 1.0")
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = ss.str()
    return false                                                   → END
13  options.minimizer_type == ceres::TRUST_REGION ? ... : ...      đúng → 14   sai → 14
14  if (!(options.max_num_line_search_step_size_iterations >= (options.minimizer_type == ceres::TRUST_REGION ? 0 : 1)))   đúng → 15   sai → 16
15  ss << "Invalid configuration. "
    ss << std::string("Solver::Options::max_num_line_search_step_size_iterations = ") << options.max_num_line_search_step_size_iterations << ". "
    ss << "Violated constraint: "
    ss << std::string("Solver::Options::max_num_line_search_step_size_iterations >= (options.minimizer_type == ceres::TRUST_REGION ? 0 : 1)")
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = ss.str()
    return false                                                   → END
16  if (!(options.line_search_sufficient_function_decrease > 0.))   đúng → 17   sai → 18
17  ss << "Invalid configuration. "
    ss << std::string("Solver::Options::line_search_sufficient_function_decrease = ") << options.line_search_sufficient_function_decrease << ". "
    ss << "Violated constraint: "
    ss << std::string("Solver::Options::line_search_sufficient_function_decrease > 0.0")
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = ss.str()
    return false                                                   → END
18  if (!(options.line_search_sufficient_function_decrease < options.line_search_sufficient_curvature_decrease))   đúng → 19   sai → 20
19  ss << "Invalid configuration. "
    ss << std::string("Solver::Options::line_search_sufficient_function_decrease = ") << options.line_search_sufficient_function_decrease << ". "
    ss << std::string("Solver::Options::line_search_sufficient_curvature_decrease = ") << options.line_search_sufficient_curvature_decrease << ". "
    ss << "Violated constraint: "
    ss << std::string("Solver::Options::line_search_sufficient_function_decrease")
    ss << std::string("< Solver::Options::line_search_sufficient_curvature_decrease.")
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = ss.str()
    return false                                                   → END
20  if (!(options.line_search_sufficient_curvature_decrease < 1.))   đúng → 21   sai → 22
21  ss << "Invalid configuration. "
    ss << std::string("Solver::Options::line_search_sufficient_curvature_decrease = ") << options.line_search_sufficient_curvature_decrease << ". "
    ss << "Violated constraint: "
    ss << std::string("Solver::Options::line_search_sufficient_curvature_decrease < 1.0")
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = ss.str()
    return false                                                   → END
22  if (!(options.max_line_search_step_expansion > 1.))            đúng → 23   sai → 24
23  ss << "Invalid configuration. "
    ss << std::string("Solver::Options::max_line_search_step_expansion = ") << options.max_line_search_step_expansion << ". "
    ss << "Violated constraint: "
    ss << std::string("Solver::Options::max_line_search_step_expansion > 1.0")
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = ss.str()
    return false                                                   → END
24  if (options.line_search_direction_type == ceres::BFGS || options.line_search_direction_type == ceres::LBFGS) && options.line_search_type != ceres::WOLFE   đúng → 25   sai → 26
25  operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = std::string("Invalid configuration: Solver::Options::line_search_type = ") + std::string(LineSearchTypeToString(options.line_search_type)) + std::string(". When using (L)BFGS, Solver::Options::line_search_type must be set to WOLFE.")
    return false                                                   → END
26  if (options.line_search_interpolation_type == ceres::BISECTION && (options.max_line_search_step_contraction > 0.5 || options.min_line_search_step_contraction < 0.5))   đúng → 27   sai → 27
27  return true                                                    → END
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1142_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
