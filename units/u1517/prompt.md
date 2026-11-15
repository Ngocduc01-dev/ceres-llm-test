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

- Hàm: `AddResidualBlock(CostFunction * cost_function, LossFunction * loss_function, double *const *const parameter_blocks, int num_parameter_blocks)`, trả về `ResidualBlockId`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::ProblemImpl`
- Vị trí: `internal/ceres/problem_impl.cc`, dòng 267–356

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
267 | ResidualBlockId ProblemImpl::AddResidualBlock(
268 |     CostFunction* cost_function,
269 |     LossFunction* loss_function,
270 |     double* const* const parameter_blocks,
271 |     int num_parameter_blocks) {
272 |   CHECK(cost_function != nullptr);
273 |   CHECK_EQ(num_parameter_blocks, cost_function->parameter_block_sizes().size());
274 | 
275 |   // Check the sizes match.
276 |   const std::vector<int32_t>& parameter_block_sizes =
277 |       cost_function->parameter_block_sizes();
278 | 
279 |   if (!options_.disable_all_safety_checks) {
280 |     CHECK_EQ(parameter_block_sizes.size(), num_parameter_blocks)
281 |         << "Number of blocks input is different than the number of blocks "
282 |         << "that the cost function expects.";
283 | 
284 |     // Check for duplicate parameter blocks.
285 |     std::vector<double*> sorted_parameter_blocks(
286 |         parameter_blocks, parameter_blocks + num_parameter_blocks);
287 |     sort(sorted_parameter_blocks.begin(), sorted_parameter_blocks.end());
288 |     const bool has_duplicate_items =
289 |         (std::adjacent_find(sorted_parameter_blocks.begin(),
290 |                             sorted_parameter_blocks.end()) !=
291 |          sorted_parameter_blocks.end());
292 |     if (has_duplicate_items) {
293 |       std::string blocks;
294 |       for (int i = 0; i < num_parameter_blocks; ++i) {
295 |         blocks += StringPrintf(" %p ", parameter_blocks[i]);
296 |       }
297 | 
298 |       LOG(FATAL) << "Duplicate parameter blocks in a residual parameter "
299 |                  << "are not allowed. Parameter block pointers: [" << blocks
300 |                  << "]";
301 |     }
302 |   }
303 | 
304 |   // Add parameter blocks and convert the double*'s to parameter blocks.
305 |   std::vector<ParameterBlock*> parameter_block_ptrs(num_parameter_blocks);
306 |   for (int i = 0; i < num_parameter_blocks; ++i) {
307 |     parameter_block_ptrs[i] = InternalAddParameterBlock(
308 |         parameter_blocks[i], parameter_block_sizes[i]);
309 |   }
310 | 
311 |   if (!options_.disable_all_safety_checks) {
312 |     // Check that the block sizes match the block sizes expected by the
313 |     // cost_function.
314 |     for (int i = 0; i < parameter_block_ptrs.size(); ++i) {
315 |       CHECK_EQ(cost_function->parameter_block_sizes()[i],
316 |                parameter_block_ptrs[i]->Size())
317 |           << "The cost function expects parameter block " << i << " of size "
318 |           << cost_function->parameter_block_sizes()[i]
319 |           << " but was given a block of size "
320 |           << parameter_block_ptrs[i]->Size();
321 |     }
322 |   }
323 | 
324 |   auto* new_residual_block =
325 |       new ResidualBlock(cost_function,
326 |                         loss_function,
327 |                         parameter_block_ptrs,
328 |                         program_->residual_blocks_.size());
329 | 
330 |   // Add dependencies on the residual to the parameter blocks.
331 |   if (options_.enable_fast_removal) {
332 |     for (int i = 0; i < num_parameter_blocks; ++i) {
333 |       parameter_block_ptrs[i]->AddResidualBlock(new_residual_block);
334 |     }
335 |   }
336 | 
337 |   program_->residual_blocks_.push_back(new_residual_block);
338 | 
339 |   if (options_.enable_fast_removal) {
340 |     residual_block_set_.insert(new_residual_block);
341 |   }
342 | 
343 |   if (options_.cost_function_ownership == TAKE_OWNERSHIP) {
344 |     // Increment the reference count, creating an entry in the table if
345 |     // needed. Note: C++ maps guarantee that new entries have default
346 |     // constructed values; this implies integers are zero initialized.
347 |     ++cost_function_ref_count_[cost_function];
348 |   }
349 | 
350 |   if (options_.loss_function_ownership == TAKE_OWNERSHIP &&
351 |       loss_function != nullptr) {
352 |     ++loss_function_ref_count_[loss_function];
353 |   }
354 | 
355 |   return new_residual_block;
356 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 10 (và 5 lệnh CHECK)

START → 1
1   CHECK(cost_function != nullptr)                                đúng → 2   sai → DỪNG
2   CHECK_EQ(num_parameter_blocks, cost_function->parameter_block_sizes().size())   đúng → 3   sai → DỪNG
3   const std::vector<int32_t> &parameter_block_sizes = cost_function->parameter_block_sizes()   → 4
4   if (!options_.disable_all_safety_checks)                       đúng → 5   sai → 12
5   CHECK_EQ(parameter_block_sizes.size(), num_parameter_blocks)   đúng → 6   sai → DỪNG
6   parameter_blocks, parameter_blocks + num_parameter_blocks
    const bool has_duplicate_items = (std::adjacent_find(sorted_parameter_blocks.begin(), sorted_parameter_blocks.end()) != sorted_parameter_blocks.end())   → 7
7   if (has_duplicate_items)                                       đúng → 8   sai → 12
8   int i = 0                                                      → 9
9   LOG(FATAL)                                                     đúng → 10   sai → DỪNG
10  blocks += StringPrintf(" %p ", parameter_blocks[i])            → 11
11  ++i                                                            → 9
12  int i = 0                                                      → 13
13  vòng for, điều kiện: i < num_parameter_blocks                  đúng → 14   sai → 16
14  parameter_block_ptrs[i] = InternalAddParameterBlock(parameter_blocks[i], parameter_block_sizes[i])   → 15
15  ++i                                                            → 13
16  if (!options_.disable_all_safety_checks)                       đúng → 17   sai → 21
17  int i = 0                                                      → 18
18  vòng for, điều kiện: i < parameter_block_ptrs.size()           đúng → 19   sai → 21
19  parameter_block_ptrs[i]->Size())                               đúng → 20   sai → DỪNG
20  ++i                                                            → 18
21  CFGNewAllocator(ResidualBlock *)
    auto *new_residual_block = new ResidualBlock(cost_function, loss_function, parameter_block_ptrs, program_->residual_blocks_.size())   → 22
22  if (options_.enable_fast_removal)                              đúng → 23   sai → 27
23  int i = 0                                                      → 24
24  vòng for, điều kiện: i < num_parameter_blocks                  đúng → 25   sai → 27
25  parameter_block_ptrs[i]->AddResidualBlock(new_residual_block)   → 26
26  ++i                                                            → 24
27  program_->residual_blocks_.push_back(new_residual_block)       → 28
28  if (options_.enable_fast_removal)                              đúng → 29   sai → 30
29  residual_block_set_.insert(new_residual_block)                 → 30
30  if (options_.cost_function_ownership == TAKE_OWNERSHIP)        đúng → 31   sai → 32
31  ++cost_function_ref_count_[cost_function]                      → 32
32  if (options_.loss_function_ownership == TAKE_OWNERSHIP && loss_function != nullptr)   đúng → 33   sai → 34
33  ++loss_function_ref_count_[loss_function]                      → 34
34  return new_residual_block                                      → END
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
#include "ceres/cost_function.h"
#include "ceres/loss_function.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"
#include "ceres/residual_block.h"
```

- Đây là method của class `ceres::internal::ProblemImpl`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `ProblemImpl`:
Các constructor:
```cpp
  ProblemImpl()
  ProblemImpl(const Problem::Options & options)
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1517_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
