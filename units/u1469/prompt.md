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

- Hàm: `GetCovarianceMatrixInTangentOrAmbientSpace(const std::vector<const double *> & parameters, bool lift_covariance_to_ambient_space, double * covariance_matrix) const`, trả về `bool`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::CovarianceImpl`
- Vị trí: `internal/ceres/covariance_impl.cc`, dòng 276–356

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
276 | bool CovarianceImpl::GetCovarianceMatrixInTangentOrAmbientSpace(
277 |     const std::vector<const double*>& parameters,
278 |     bool lift_covariance_to_ambient_space,
279 |     double* covariance_matrix) const {
280 |   CHECK(is_computed_)
281 |       << "Covariance::GetCovarianceMatrix called before Covariance::Compute";
282 |   CHECK(is_valid_)
283 |       << "Covariance::GetCovarianceMatrix called when Covariance::Compute "
284 |       << "returned false.";
285 | 
286 |   const ProblemImpl::ParameterMap& parameter_map = problem_->parameter_map();
287 |   // For OpenMP compatibility we need to define these vectors in advance
288 |   const int num_parameters = parameters.size();
289 |   std::vector<int> parameter_sizes;
290 |   std::vector<int> cum_parameter_size;
291 |   parameter_sizes.reserve(num_parameters);
292 |   cum_parameter_size.resize(num_parameters + 1);
293 |   cum_parameter_size[0] = 0;
294 |   for (int i = 0; i < num_parameters; ++i) {
295 |     ParameterBlock* block =
296 |         FindOrDie(parameter_map, const_cast<double*>(parameters[i]));
297 |     if (lift_covariance_to_ambient_space) {
298 |       parameter_sizes.push_back(block->Size());
299 |     } else {
300 |       parameter_sizes.push_back(block->TangentSize());
301 |     }
302 |   }
303 |   std::partial_sum(parameter_sizes.begin(),
304 |                    parameter_sizes.end(),
305 |                    cum_parameter_size.begin() + 1);
306 |   const int max_covariance_block_size =
307 |       *std::max_element(parameter_sizes.begin(), parameter_sizes.end());
308 |   const int covariance_size = cum_parameter_size.back();
309 | 
310 |   // Assemble the blocks in the covariance matrix.
311 |   MatrixRef covariance(covariance_matrix, covariance_size, covariance_size);
312 |   const int num_threads = options_.num_threads;
313 |   auto workspace = std::make_unique<double[]>(
314 |       num_threads * max_covariance_block_size * max_covariance_block_size);
315 | 
316 |   bool success = true;
317 | 
318 |   // Technically the following code is a double nested loop where
319 |   // i = 1:n, j = i:n.
320 |   int iteration_count = (num_parameters * (num_parameters + 1)) / 2;
321 |   problem_->context()->EnsureMinimumThreads(num_threads);
322 |   ParallelFor(problem_->context(),
323 |               0,
324 |               iteration_count,
325 |               num_threads,
326 |               [&](int thread_id, int k) {
327 |                 int i, j;
328 |                 LinearIndexToUpperTriangularIndex(k, num_parameters, &i, &j);
329 | 
330 |                 int covariance_row_idx = cum_parameter_size[i];
331 |                 int covariance_col_idx = cum_parameter_size[j];
332 |                 int size_i = parameter_sizes[i];
333 |                 int size_j = parameter_sizes[j];
334 |                 double* covariance_block =
335 |                     workspace.get() + thread_id * max_covariance_block_size *
336 |                                           max_covariance_block_size;
337 |                 if (!GetCovarianceBlockInTangentOrAmbientSpace(
338 |                         parameters[i],
339 |                         parameters[j],
340 |                         lift_covariance_to_ambient_space,
341 |                         covariance_block)) {
342 |                   success = false;
343 |                 }
344 | 
345 |                 covariance.block(
346 |                     covariance_row_idx, covariance_col_idx, size_i, size_j) =
347 |                     MatrixRef(covariance_block, size_i, size_j);
348 | 
349 |                 if (i != j) {
350 |                   covariance.block(
351 |                       covariance_col_idx, covariance_row_idx, size_j, size_i) =
352 |                       MatrixRef(covariance_block, size_i, size_j).transpose();
353 |                 }
354 |               });
355 |   return success;
356 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 2 (và 2 lệnh CHECK)

START → 1
1   CHECK(is_computed_)                                            đúng → 2   sai → DỪNG
2   CHECK(is_valid_)                                               đúng → 3   sai → DỪNG
3   vòng for, điều kiện: i < num_parameters                        đúng → 4   sai → 9
4   FindOrDie(parameter_map, const_cast<double *>(parameters[i]) (CXXConstCastExpr, NoOp, double *))
    ParameterBlock *block = FindOrDie(parameter_map, const_cast<double *>(parameters[i]))   → 5
5   if (lift_covariance_to_ambient_space)                          đúng → 6   sai → 8
6   parameter_sizes.push_back(block->Size())                       → 7
7   ++i                                                            → 3
8   parameter_sizes.push_back(block->TangentSize())                → 7
9   const int max_covariance_block_size = * std::max_element(parameter_sizes.begin(), parameter_sizes.end())
    const int covariance_size = cum_parameter_size.back()
    covariance_matrix, covariance_size, covariance_size
    const int num_threads = options_.num_threads
    bool success = true
    int iteration_count = (num_parameters * (num_parameters + 1)) / 2
    problem_->context()->EnsureMinimumThreads(num_threads)
    ParallelFor (ImplicitCastExpr, FunctionToPointerDecay, void (*)(ContextImpl *, int, int, int, class (lambda at /work/ceres-solver/internal/ceres/covariance_impl.cc:326:15) &&, int))(problem_->context(), 0, iteration_count, num_threads, [&](int thread_id, int k) {)
    return success                                                 → END
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
#include "ceres/covariance_impl.h"
#include "ceres/map_util.h"
#include "ceres/parallel_for.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"
```

- Đây là method của class `ceres::internal::CovarianceImpl`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `CovarianceImpl`:
Các constructor:
```cpp
  CovarianceImpl(const Covariance::Options & options)
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1469_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
