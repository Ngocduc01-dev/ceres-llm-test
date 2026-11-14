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

- Hàm: `ComputeCovarianceSparsity(const CovarianceBlocks & original_covariance_blocks, ProblemImpl * problem)`, trả về `bool`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::CovarianceImpl`
- Vị trí: `internal/ceres/covariance_impl.cc`, dòng 360–498

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
360 | bool CovarianceImpl::ComputeCovarianceSparsity(
361 |     const CovarianceBlocks& original_covariance_blocks, ProblemImpl* problem) {
362 |   EventLogger event_logger("CovarianceImpl::ComputeCovarianceSparsity");
363 | 
364 |   // Determine an ordering for the parameter block, by sorting the
365 |   // parameter blocks by their pointers.
366 |   std::vector<double*> all_parameter_blocks;
367 |   problem->GetParameterBlocks(&all_parameter_blocks);
368 |   const ProblemImpl::ParameterMap& parameter_map = problem->parameter_map();
369 |   std::unordered_set<ParameterBlock*> parameter_blocks_in_use;
370 |   std::vector<ResidualBlock*> residual_blocks;
371 |   problem->GetResidualBlocks(&residual_blocks);
372 | 
373 |   for (auto* residual_block : residual_blocks) {
374 |     parameter_blocks_in_use.insert(residual_block->parameter_blocks(),
375 |                                    residual_block->parameter_blocks() +
376 |                                        residual_block->NumParameterBlocks());
377 |   }
378 | 
379 |   constant_parameter_blocks_.clear();
380 |   std::vector<double*>& active_parameter_blocks =
381 |       evaluate_options_.parameter_blocks;
382 |   active_parameter_blocks.clear();
383 |   for (auto* parameter_block : all_parameter_blocks) {
384 |     ParameterBlock* block = FindOrDie(parameter_map, parameter_block);
385 |     if (!block->IsConstant() && (parameter_blocks_in_use.count(block) > 0)) {
386 |       active_parameter_blocks.push_back(parameter_block);
387 |     } else {
388 |       constant_parameter_blocks_.insert(parameter_block);
389 |     }
390 |   }
391 | 
392 |   std::sort(active_parameter_blocks.begin(), active_parameter_blocks.end());
393 | 
394 |   // Compute the number of rows.  Map each parameter block to the
395 |   // first row corresponding to it in the covariance matrix using the
396 |   // ordering of parameter blocks just constructed.
397 |   int num_rows = 0;
398 |   parameter_block_to_row_index_.clear();
399 |   for (auto* parameter_block : active_parameter_blocks) {
400 |     const int parameter_block_size =
401 |         problem->ParameterBlockTangentSize(parameter_block);
402 |     parameter_block_to_row_index_[parameter_block] = num_rows;
403 |     num_rows += parameter_block_size;
404 |   }
405 | 
406 |   // Compute the number of non-zeros in the covariance matrix.  Along
407 |   // the way flip any covariance blocks which are in the lower
408 |   // triangular part of the matrix.
409 |   int num_nonzeros = 0;
410 |   CovarianceBlocks covariance_blocks;
411 |   for (const auto& block_pair : original_covariance_blocks) {
412 |     if (constant_parameter_blocks_.count(block_pair.first) > 0 ||
413 |         constant_parameter_blocks_.count(block_pair.second) > 0) {
414 |       continue;
415 |     }
416 | 
417 |     int index1 = FindOrDie(parameter_block_to_row_index_, block_pair.first);
418 |     int index2 = FindOrDie(parameter_block_to_row_index_, block_pair.second);
419 |     const int size1 = problem->ParameterBlockTangentSize(block_pair.first);
420 |     const int size2 = problem->ParameterBlockTangentSize(block_pair.second);
421 |     num_nonzeros += size1 * size2;
422 | 
423 |     // Make sure we are constructing a block upper triangular matrix.
424 |     if (index1 > index2) {
425 |       covariance_blocks.push_back(
426 |           std::make_pair(block_pair.second, block_pair.first));
427 |     } else {
428 |       covariance_blocks.push_back(block_pair);
429 |     }
430 |   }
431 | 
432 |   if (covariance_blocks.empty()) {
433 |     VLOG(2) << "No non-zero covariance blocks found";
434 |     covariance_matrix_ = nullptr;
435 |     return true;
436 |   }
437 | 
438 |   // Sort the block pairs. As a consequence we get the covariance
439 |   // blocks as they will occur in the CompressedRowSparseMatrix that
440 |   // will store the covariance.
441 |   std::sort(covariance_blocks.begin(), covariance_blocks.end());
442 | 
443 |   // Fill the sparsity pattern of the covariance matrix.
444 |   covariance_matrix_ = std::make_unique<CompressedRowSparseMatrix>(
445 |       num_rows, num_rows, num_nonzeros);
446 | 
447 |   int* rows = covariance_matrix_->mutable_rows();
448 |   int* cols = covariance_matrix_->mutable_cols();
449 | 
450 |   // Iterate over parameter blocks and in turn over the rows of the
451 |   // covariance matrix. For each parameter block, look in the upper
452 |   // triangular part of the covariance matrix to see if there are any
453 |   // blocks requested by the user. If this is the case then fill out a
454 |   // set of compressed rows corresponding to this parameter block.
455 |   //
456 |   // The key thing that makes this loop work is the fact that the
457 |   // row/columns of the covariance matrix are ordered by the pointer
458 |   // values of the parameter blocks. Thus iterating over the keys of
459 |   // parameter_block_to_row_index_ corresponds to iterating over the
460 |   // rows of the covariance matrix in order.
461 |   int i = 0;       // index into covariance_blocks.
462 |   int cursor = 0;  // index into the covariance matrix.
463 |   for (const auto& entry : parameter_block_to_row_index_) {
464 |     const double* row_block = entry.first;
465 |     const int row_block_size = problem->ParameterBlockTangentSize(row_block);
466 |     int row_begin = entry.second;
467 | 
468 |     // Iterate over the covariance blocks contained in this row block
469 |     // and count the number of columns in this row block.
470 |     int num_col_blocks = 0;
471 |     for (int j = i; j < covariance_blocks.size(); ++j, ++num_col_blocks) {
472 |       const std::pair<const double*, const double*>& block_pair =
473 |           covariance_blocks[j];
474 |       if (block_pair.first != row_block) {
475 |         break;
476 |       }
477 |     }
478 | 
479 |     // Fill out all the compressed rows for this parameter block.
480 |     for (int r = 0; r < row_block_size; ++r) {
481 |       rows[row_begin + r] = cursor;
482 |       for (int c = 0; c < num_col_blocks; ++c) {
483 |         const double* col_block = covariance_blocks[i + c].second;
484 |         const int col_block_size =
485 |             problem->ParameterBlockTangentSize(col_block);
486 |         int col_begin = FindOrDie(parameter_block_to_row_index_, col_block);
487 |         for (int k = 0; k < col_block_size; ++k) {
488 |           cols[cursor++] = col_begin++;
489 |         }
490 |       }
491 |     }
492 | 
493 |     i += num_col_blocks;
494 |   }
495 | 
496 |   rows[num_rows] = cursor;
497 |   return true;
498 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 14

START → 1
1   "CovarianceImpl::ComputeCovarianceSparsity"
    problem->GetParameterBlocks(&all_parameter_blocks)
    const ProblemImpl::ParameterMap &parameter_map = problem->parameter_map()
    problem->GetResidualBlocks(&residual_blocks)                   → 2
2   for (auto *residual_block : residual_blocks)                   đúng → 3   sai → 5
3   auto *residual_block
    parameter_blocks_in_use.insert(residual_block->parameter_blocks(), residual_block->parameter_blocks() + residual_block->NumParameterBlocks())   → 4
4   ++ (bước tiếp của vòng for)                                    → 2
5   constant_parameter_blocks_.clear()
    std::vector<double *> &active_parameter_blocks = evaluate_options_.parameter_blocks
    active_parameter_blocks.clear()                                → 6
6   for (auto *parameter_block : all_parameter_blocks)             đúng → 7   sai → 12
7   auto *parameter_block
    ParameterBlock *block = FindOrDie(parameter_map, parameter_block)   → 8
8   if (!block->IsConstant() && (parameter_blocks_in_use.count(block) > 0))   đúng → 9   sai → 11
9   active_parameter_blocks.push_back(parameter_block)             → 10
10  ++ (bước tiếp của vòng for)                                    → 6
11  constant_parameter_blocks_.insert(parameter_block)             → 10
12  int num_rows = 0
    parameter_block_to_row_index_.clear()                          → 13
13  for (auto *parameter_block : active_parameter_blocks)          đúng → 14   sai → 16
14  auto *parameter_block
    const int parameter_block_size = problem->ParameterBlockTangentSize(parameter_block)
    parameter_block_to_row_index_[parameter_block] = num_rows
    num_rows += parameter_block_size                               → 15
15  ++ (bước tiếp của vòng for)                                    → 13
16  int num_nonzeros = 0                                           → 17
17  for (const auto &block_pair : original_covariance_blocks)      đúng → 18   sai → 26
18  const auto &block_pair                                         → 19
19  if (constant_parameter_blocks_.count(block_pair.first) > 0 || constant_parameter_blocks_.count(block_pair.second) > 0)   đúng → 20   sai → 22
20  continue                                                       → 21
21  ++ (bước tiếp của vòng for)                                    → 17
22  int index1 = FindOrDie(parameter_block_to_row_index_, block_pair.first)
    int index2 = FindOrDie(parameter_block_to_row_index_, block_pair.second)
    const int size1 = problem->ParameterBlockTangentSize(block_pair.first)
    const int size2 = problem->ParameterBlockTangentSize(block_pair.second)
    num_nonzeros += size1 * size2                                  → 23
23  if (index1 > index2)                                           đúng → 24   sai → 25
24  covariance_blocks.push_back(std::make_pair(block_pair.second, block_pair.first))   → 21
25  covariance_blocks.push_back(block_pair)                        → 21
26  if (covariance_blocks.empty())                                 đúng → END   sai → 27
27  covariance_matrix_ = std::make_unique<CompressedRowSparseMatrix>(num_rows, num_rows, num_nonzeros)
    int *rows = covariance_matrix_->mutable_rows()
    int *cols = covariance_matrix_->mutable_cols()
    int i = 0
    int cursor = 0                                                 → 28
28  for (const auto &entry : parameter_block_to_row_index_)        đúng → 29   sai → 47
29  const auto &entry
    const double *row_block = entry.first
    const int row_block_size = problem->ParameterBlockTangentSize(row_block)
    int row_begin = entry.second
    int num_col_blocks = 0
    int j = i                                                      → 30
30  vòng for, điều kiện: j < covariance_blocks.size()              đúng → 31   sai → 34
31  const std::pair<const double *, const double *> &block_pair = covariance_blocks[j]   → 32
32  if (block_pair.first != row_block)                             đúng → 33   sai → 46
33  break                                                          → 34
34  int r = 0                                                      → 35
35  vòng for, điều kiện: r < row_block_size                        đúng → 36   sai → 44
36  rows[row_begin + r] = cursor
    int c = 0                                                      → 37
37  vòng for, điều kiện: c < num_col_blocks                        đúng → 38   sai → 43
38  const double *col_block = covariance_blocks[i + c].second
    const int col_block_size = problem->ParameterBlockTangentSize(col_block)
    int col_begin = FindOrDie(parameter_block_to_row_index_, col_block)
    int k = 0                                                      → 39
39  vòng for, điều kiện: k < col_block_size                        đúng → 40   sai → 42
40  cols[cursor++] = col_begin++                                   → 41
41  ++k                                                            → 39
42  ++c                                                            → 37
43  ++r                                                            → 35
44  i += num_col_blocks                                            → 45
45  ++ (bước tiếp của vòng for)                                    → 28
46  ++j                                                            → 30
47  rows[num_rows] = cursor
    return true                                                    → END
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
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/covariance_impl.h"
#include "ceres/map_util.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"
#include "ceres/residual_block.h"
#include "ceres/wall_time.h"
```

- Đây là method của class `ceres::internal::CovarianceImpl`: tạo một object của class rồi gọi method trên object đó.

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1446_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
