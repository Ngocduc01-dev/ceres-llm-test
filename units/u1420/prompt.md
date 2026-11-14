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

- Hàm: `OptionsAreValidForIterativeSchur(const Solver::Options & options, std::string * error)`, trả về `bool`
- Loại: hàm tự do (không thuộc class)
- Namespace: `ceres::(namespace không tên)`
- Vị trí: `internal/ceres/solver.cc`, dòng 253–305

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
253 | bool OptionsAreValidForIterativeSchur(const Solver::Options& options,
254 |                                       std::string* error) {
255 |   CHECK_EQ(options.linear_solver_type, ITERATIVE_SCHUR);
256 |   if (options.dynamic_sparsity) {
257 |     *error = "Dynamic sparsity is only supported with SPARSE_NORMAL_CHOLESKY.";
258 |     return false;
259 |   }
260 | 
261 |   if (options.use_explicit_schur_complement) {
262 |     if (options.preconditioner_type != SCHUR_JACOBI) {
263 |       *error =
264 |           "use_explicit_schur_complement only supports "
265 |           "SCHUR_JACOBI as the preconditioner.";
266 |       return false;
267 |     }
268 |     if (options.use_spse_initialization) {
269 |       *error =
270 |           "use_explicit_schur_complement does not support "
271 |           "use_spse_initialization.";
272 |       return false;
273 |     }
274 |   }
275 | 
276 |   if (options.use_spse_initialization ||
277 |       options.preconditioner_type == SCHUR_POWER_SERIES_EXPANSION) {
278 |     OPTION_GE(max_num_spse_iterations, 1)
279 |     OPTION_GE(spse_tolerance, 0.0)
280 |   }
281 | 
282 |   if (options.use_mixed_precision_solves) {
283 |     *error = "Can't use use_mixed_precision_solves with ITERATIVE_SCHUR";
284 |     return false;
285 |   }
286 | 
287 |   if (options.dynamic_sparsity) {
288 |     *error = "Dynamic sparsity is only supported with SPARSE_NORMAL_CHOLESKY.";
289 |     return false;
290 |   }
291 | 
292 |   if (options.preconditioner_type == SUBSET) {
293 |     *error = "Can't use SUBSET preconditioner with ITERATIVE_SCHUR";
294 |     return false;
295 |   }
296 | 
297 |   // CLUSTER_JACOBI and CLUSTER_TRIDIAGONAL require sparse Cholesky
298 |   // factorization.
299 |   if (options.preconditioner_type == CLUSTER_JACOBI ||
300 |       options.preconditioner_type == CLUSTER_TRIDIAGONAL) {
301 |     return OptionsAreValidForSparseCholeskyBasedSolver(options, error);
302 |   }
303 | 
304 |   return true;
305 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 11 (và 1 lệnh CHECK)

START → 1
1   CHECK_EQ(options.linear_solver_type, ITERATIVE_SCHUR)          đúng → 2   sai → DỪNG
2   if (options.dynamic_sparsity)                                  đúng → 3   sai → 4
3   *error = "Dynamic sparsity is only supported with SPARSE_NORMAL_CHOLESKY."
    return false                                                   → END
4   if (options.use_explicit_schur_complement)                     đúng → 5   sai → 9
5   if (options.preconditioner_type != SCHUR_JACOBI)               đúng → 6   sai → 7
6   *error = "use_explicit_schur_complement only supports SCHUR_JACOBI as the preconditioner."
    return false                                                   → END
7   if (options.use_spse_initialization)                           đúng → 8   sai → 9
8   *error = "use_explicit_schur_complement does not support use_spse_initialization."
    return false                                                   → END
9   if (options.use_spse_initialization || options.preconditioner_type == SCHUR_POWER_SERIES_EXPANSION)   đúng → 10   sai → 14
10  if (!(options.max_num_spse_iterations >= 1))                   đúng → 11   sai → 12
11  ss << "Invalid configuration. "
    ss << std::string("Solver::Options::max_num_spse_iterations = ") << options.max_num_spse_iterations << ". "
    ss << "Violated constraint: "
    ss << std::string("Solver::Options::max_num_spse_iterations >= 1")
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = ss.str()
    return false                                                   → END
12  if (!(options.spse_tolerance >= 0.))                           đúng → 13   sai → 14
13  ss << "Invalid configuration. "
    ss << std::string("Solver::Options::spse_tolerance = ") << options.spse_tolerance << ". "
    ss << "Violated constraint: "
    ss << std::string("Solver::Options::spse_tolerance >= 0.0")
    operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = ss.str()
    return false                                                   → END
14  if (options.use_mixed_precision_solves)                        đúng → 15   sai → 16
15  *error = "Can't use use_mixed_precision_solves with ITERATIVE_SCHUR"
    return false                                                   → END
16  if (options.dynamic_sparsity)                                  đúng → 17   sai → 18
17  *error = "Dynamic sparsity is only supported with SPARSE_NORMAL_CHOLESKY."
    return false                                                   → END
18  if (options.preconditioner_type == SUBSET)                     đúng → 19   sai → 20
19  *error = "Can't use SUBSET preconditioner with ITERATIVE_SCHUR"
    return false                                                   → END
20  if (options.preconditioner_type == CLUSTER_JACOBI || options.preconditioner_type == CLUSTER_TRIDIAGONAL)   đúng → 21   sai → 22
21  return OptionsAreValidForSparseCholeskyBasedSolver(options, error)   → END
22  return true                                                    → END
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1420_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
