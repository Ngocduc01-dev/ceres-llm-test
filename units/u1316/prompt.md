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

- Hàm: `OptionsAreValidForSparseCholeskyBasedSolver(const Solver::Options & options, std::string * error)`, trả về `bool`
- Loại: hàm tự do (không thuộc class)
- Namespace: `ceres::(namespace không tên)`
- Vị trí: `internal/ceres/solver.cc`, dòng 141–197

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
141 | bool OptionsAreValidForSparseCholeskyBasedSolver(const Solver::Options& options,
142 |                                                  std::string* error) {
143 |   const char* library_name = SparseLinearAlgebraLibraryTypeToString(
144 |       options.sparse_linear_algebra_library_type);
145 |   // Sparse factorization based solvers and some preconditioners require a
146 |   // sparse Cholesky factorization.
147 |   const char* solver_name =
148 |       IsIterativeSolver(options.linear_solver_type)
149 |           ? PreconditionerTypeToString(options.preconditioner_type)
150 |           : LinearSolverTypeToString(options.linear_solver_type);
151 | 
152 |   constexpr char kNoSparseFormat[] =
153 |       "Can't use %s with sparse_linear_algebra_library_type = %s.";
154 |   constexpr char kNoLibraryFormat[] =
155 |       "Can't use %s sparse_linear_algebra_library_type = %s, because support "
156 |       "was not enabled when Ceres Solver was built.";
157 |   constexpr char kNoNesdisFormat[] =
158 |       "NESDIS is not available with sparse_linear_algebra_library_type = %s.";
159 |   constexpr char kMixedFormat[] =
160 |       "use_mixed_precision_solves with %s is not supported with "
161 |       "sparse_linear_algebra_library_type = %s";
162 |   constexpr char kDynamicSparsityFormat[] =
163 |       "dynamic sparsity is not supported with "
164 |       "sparse_linear_algebra_library_type = %s";
165 | 
166 |   if (options.sparse_linear_algebra_library_type == NO_SPARSE) {
167 |     *error = StringPrintf(kNoSparseFormat, solver_name, library_name);
168 |     return false;
169 |   }
170 | 
171 |   if (!IsSparseLinearAlgebraLibraryTypeAvailable(
172 |           options.sparse_linear_algebra_library_type)) {
173 |     *error = StringPrintf(kNoLibraryFormat, solver_name, library_name);
174 |     return false;
175 |   }
176 | 
177 |   if (options.linear_solver_ordering_type == ceres::NESDIS &&
178 |       !IsNestedDissectionAvailable(
179 |           options.sparse_linear_algebra_library_type)) {
180 |     *error = StringPrintf(kNoNesdisFormat, library_name);
181 |     return false;
182 |   }
183 | 
184 |   if (options.use_mixed_precision_solves &&
185 |       options.sparse_linear_algebra_library_type == SUITE_SPARSE) {
186 |     *error = StringPrintf(kMixedFormat, solver_name, library_name);
187 |     return false;
188 |   }
189 | 
190 |   if (options.dynamic_sparsity &&
191 |       options.sparse_linear_algebra_library_type == ACCELERATE_SPARSE) {
192 |     *error = StringPrintf(kDynamicSparsityFormat, library_name);
193 |     return false;
194 |   }
195 | 
196 |   return true;
197 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 6

START → 1
1   const char *library_name = SparseLinearAlgebraLibraryTypeToString(options.sparse_linear_algebra_library_type)   → 2
2   IsIterativeSolver(options.linear_solver_type) ? ... : ...      đúng → 3   sai → 3
3   const char *solver_name = IsIterativeSolver(options.linear_solver_type) ? PreconditionerTypeToString(options.preconditioner_type) : LinearSolverTypeToString(options.linear_solver_type)
    constexpr char kNoSparseFormat[] = "Can't use %s with sparse_linear_algebra_library_type = %s."
    constexpr char kNoLibraryFormat[] = "Can't use %s sparse_linear_algebra_library_type = %s, because support was not enabled when Ceres Solver was built."
    constexpr char kNoNesdisFormat[] = "NESDIS is not available with sparse_linear_algebra_library_type = %s."
    constexpr char kMixedFormat[] = "use_mixed_precision_solves with %s is not supported with sparse_linear_algebra_library_type = %s"
    constexpr char kDynamicSparsityFormat[] = "dynamic sparsity is not supported with sparse_linear_algebra_library_type = %s"   → 4
4   if (options.sparse_linear_algebra_library_type == NO_SPARSE)   đúng → 5   sai → 6
5   operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = StringPrintf(kNoSparseFormat, solver_name, library_name)
    return false                                                   → END
6   if (!IsSparseLinearAlgebraLibraryTypeAvailable(options.sparse_linear_algebra_library_type))   đúng → 7   sai → 8
7   operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = StringPrintf(kNoLibraryFormat, solver_name, library_name)
    return false                                                   → END
8   if (options.linear_solver_ordering_type == ceres::NESDIS && !IsNestedDissectionAvailable(options.sparse_linear_algebra_library_type))   đúng → 9   sai → 10
9   operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = StringPrintf(kNoNesdisFormat, library_name)
    return false                                                   → END
10  if (options.use_mixed_precision_solves && options.sparse_linear_algebra_library_type == SUITE_SPARSE)   đúng → 11   sai → 12
11  operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = StringPrintf(kMixedFormat, solver_name, library_name)
    return false                                                   → END
12  if (options.dynamic_sparsity && options.sparse_linear_algebra_library_type == ACCELERATE_SPARSE)   đúng → 13   sai → 14
13  operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = StringPrintf(kDynamicSparsityFormat, library_name)
    return false                                                   → END
14  return true                                                    → END
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1316_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
