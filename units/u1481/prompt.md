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

- Hàm: `RemoveFixedBlocks(std::vector<double *> * removed_parameter_blocks, double * fixed_cost, std::string * error)`, trả về `bool`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::Program`
- Vị trí: `internal/ceres/program.cc`, dòng 305–411

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
305 | bool Program::RemoveFixedBlocks(std::vector<double*>* removed_parameter_blocks,
306 |                                 double* fixed_cost,
307 |                                 std::string* error) {
308 |   CHECK(removed_parameter_blocks != nullptr);
309 |   CHECK(fixed_cost != nullptr);
310 |   CHECK(error != nullptr);
311 | 
312 |   std::unique_ptr<double[]> residual_block_evaluate_scratch;
313 |   residual_block_evaluate_scratch =
314 |       std::make_unique<double[]>(MaxScratchDoublesNeededForEvaluate());
315 |   *fixed_cost = 0.0;
316 | 
317 |   bool need_to_call_prepare_for_evaluation = evaluation_callback_ != nullptr;
318 | 
319 |   // Mark all the parameters as unused. Abuse the index member of the
320 |   // parameter blocks for the marking.
321 |   for (auto* parameter_block : parameter_blocks_) {
322 |     parameter_block->set_index(-1);
323 |   }
324 | 
325 |   // Filter out residual that have all-constant parameters, and mark
326 |   // all the parameter blocks that appear in residuals.
327 |   int num_active_residual_blocks = 0;
328 |   for (int i = 0; i < residual_blocks_.size(); ++i) {
329 |     ResidualBlock* residual_block = residual_blocks_[i];
330 |     int num_parameter_blocks = residual_block->NumParameterBlocks();
331 | 
332 |     // Determine if the residual block is fixed, and also mark varying
333 |     // parameters that appear in the residual block.
334 |     bool all_constant = true;
335 |     for (int k = 0; k < num_parameter_blocks; k++) {
336 |       ParameterBlock* parameter_block = residual_block->parameter_blocks()[k];
337 |       if (!parameter_block->IsConstant()) {
338 |         all_constant = false;
339 |         parameter_block->set_index(1);
340 |       }
341 |     }
342 | 
343 |     if (!all_constant) {
344 |       residual_blocks_[num_active_residual_blocks++] = residual_block;
345 |       continue;
346 |     }
347 | 
348 |     // This is an exceedingly rare case, where the user has residual
349 |     // blocks which are effectively constant but they are also
350 |     // performance sensitive enough to add an EvaluationCallback.
351 |     //
352 |     // In this case before we evaluate the cost of the constant
353 |     // residual blocks, we must call
354 |     // EvaluationCallback::PrepareForEvaluation(). Because this call
355 |     // can be costly, we only call this if we actually encounter a
356 |     // residual block with all constant parameter blocks.
357 |     //
358 |     // It is worth nothing that there is a minor inefficiency here,
359 |     // that the iteration 0 of TrustRegionMinimizer will also cause
360 |     // PrepareForEvaluation to be called on the same point, but with
361 |     // evaluate_jacobians = true. We could try and optimize this here,
362 |     // but given the rarity of this case, the additional complexity
363 |     // and long range dependency is not worth it.
364 |     if (need_to_call_prepare_for_evaluation) {
365 |       constexpr bool kNewPoint = true;
366 |       constexpr bool kDoNotEvaluateJacobians = false;
367 |       evaluation_callback_->PrepareForEvaluation(kDoNotEvaluateJacobians,
368 |                                                  kNewPoint);
369 |       need_to_call_prepare_for_evaluation = false;
370 |     }
371 | 
372 |     // The residual is constant and will be removed, so its cost is
373 |     // added to the variable fixed_cost.
374 |     double cost = 0.0;
375 |     if (!residual_block->Evaluate(true,
376 |                                   &cost,
377 |                                   nullptr,
378 |                                   nullptr,
379 |                                   residual_block_evaluate_scratch.get())) {
380 |       *error = StringPrintf(
381 |           "Evaluation of the residual %d failed during "
382 |           "removal of fixed residual blocks.",
383 |           i);
384 |       return false;
385 |     }
386 | 
387 |     *fixed_cost += cost;
388 |   }
389 |   residual_blocks_.resize(num_active_residual_blocks);
390 | 
391 |   // Filter out unused or fixed parameter blocks.
392 |   int num_active_parameter_blocks = 0;
393 |   removed_parameter_blocks->clear();
394 |   for (auto* parameter_block : parameter_blocks_) {
395 |     if (parameter_block->index() == -1) {
396 |       removed_parameter_blocks->push_back(
397 |           parameter_block->mutable_user_state());
398 |     } else {
399 |       parameter_blocks_[num_active_parameter_blocks++] = parameter_block;
400 |     }
401 |   }
402 |   parameter_blocks_.resize(num_active_parameter_blocks);
403 | 
404 |   if (!(((NumResidualBlocks() == 0) && (NumParameterBlocks() == 0)) ||
405 |         ((NumResidualBlocks() != 0) && (NumParameterBlocks() != 0)))) {
406 |     *error = "Congratulations, you found a bug in Ceres. Please report it.";
407 |     return false;
408 |   }
409 | 
410 |   return true;
411 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 10 (và 3 lệnh CHECK)

START → 1
1   CHECK(removed_parameter_blocks != nullptr)                     đúng → 2   sai → DỪNG
2   CHECK(fixed_cost != nullptr)                                   đúng → 3   sai → DỪNG
3   CHECK(error != nullptr)                                        đúng → 4   sai → DỪNG
4   for (auto *parameter_block : parameter_blocks_)                đúng → 5   sai → 7
5   auto *parameter_block
    parameter_block->set_index(-1)                                 → 6
6   ++ (bước tiếp của vòng for)                                    → 4
7   int num_active_residual_blocks = 0
    int i = 0                                                      → 8
8   vòng for, điều kiện: i < residual_blocks_.size()               đúng → 9   sai → 24
9   ResidualBlock *residual_block = residual_blocks_[i]
    int num_parameter_blocks = residual_block->NumParameterBlocks()
    bool all_constant = true
    int k = 0                                                      → 10
10  vòng for, điều kiện: k < num_parameter_blocks                  đúng → 11   sai → 15
11  ParameterBlock *parameter_block = residual_block->parameter_blocks()[k]   → 12
12  if (!parameter_block->IsConstant())                            đúng → 13   sai → 14
13  all_constant = false
    parameter_block->set_index(1)                                  → 14
14  k++                                                            → 10
15  if (!all_constant)                                             đúng → 16   sai → 18
16  residual_blocks_[num_active_residual_blocks++] = residual_block
    continue                                                       → 17
17  ++i                                                            → 8
18  if (need_to_call_prepare_for_evaluation)                       đúng → 19   sai → 20
19  constexpr bool kNewPoint = true
    constexpr bool kDoNotEvaluateJacobians = false
    evaluation_callback_->PrepareForEvaluation(kDoNotEvaluateJacobians, kNewPoint)
    need_to_call_prepare_for_evaluation = false                    → 20
20  double cost = 0.                                               → 21
21  if (!residual_block->Evaluate(true, &cost, nullptr, nullptr, residual_block_evaluate_scratch.get()))   đúng → 22   sai → 23
22  operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    *error = StringPrintf("Evaluation of the residual %d failed during removal of fixed residual blocks.", i)
    return false                                                   → END
23  *fixed_cost += cost                                            → 17
24  residual_blocks_.resize(num_active_residual_blocks)
    int num_active_parameter_blocks = 0
    removed_parameter_blocks->clear()                              → 25
25  for (auto *parameter_block : parameter_blocks_)                đúng → 26   sai → 31
26  auto *parameter_block                                          → 27
27  if (parameter_block->index() == -1)                            đúng → 28   sai → 30
28  removed_parameter_blocks->push_back(parameter_block->mutable_user_state())   → 29
29  ++ (bước tiếp của vòng for)                                    → 25
30  parameter_blocks_[num_active_parameter_blocks++] = parameter_block   → 29
31  parameter_blocks_.resize(num_active_parameter_blocks)          → 32
32  if (!(((NumResidualBlocks() == 0) && (NumParameterBlocks() == 0)) || ((NumResidualBlocks() != 0) && (NumParameterBlocks() != 0))))   đúng → 33   sai → 34
33  *error = "Congratulations, you found a bug in Ceres. Please report it."
    return false                                                   → END
34  return true                                                    → END
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
#include "ceres/evaluation_callback.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"
#include "ceres/residual_block.h"
```

- Method này là `private` (bên ngoài class không gọi được). Thêm 2 dòng `#define private public` và `#define protected public` **sau** `#include "gtest/gtest.h"` và **trước** các `#include` của Ceres.
- Đây là method của class `ceres::internal::Program`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `Program`:
Các constructor:
```cpp
  Program()
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1481_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
