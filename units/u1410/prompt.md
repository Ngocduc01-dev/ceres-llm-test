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

- Hàm: `LexicographicallyOrderResidualBlocks(const int size_of_first_elimination_group, Program * program, std::string *)`, trả về `bool`
- Loại: hàm tự do (không thuộc class)
- Namespace: `ceres::internal`
- Vị trí: `internal/ceres/reorder_program.cc`, dòng 254–335

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
254 | bool LexicographicallyOrderResidualBlocks(
255 |     const int size_of_first_elimination_group,
256 |     Program* program,
257 |     std::string* /*error*/) {
258 |   CHECK_GE(size_of_first_elimination_group, 1)
259 |       << "Congratulations, you found a Ceres bug! Please report this error "
260 |       << "to the developers.";
261 | 
262 |   // Create a histogram of the number of residuals for each E block. There is an
263 |   // extra bucket at the end to catch all non-eliminated F blocks.
264 |   std::vector<int> residual_blocks_per_e_block(size_of_first_elimination_group +
265 |                                                1);
266 |   std::vector<ResidualBlock*>* residual_blocks =
267 |       program->mutable_residual_blocks();
268 |   std::vector<int> min_position_per_residual(residual_blocks->size());
269 |   for (int i = 0; i < residual_blocks->size(); ++i) {
270 |     ResidualBlock* residual_block = (*residual_blocks)[i];
271 |     int position =
272 |         MinParameterBlock(residual_block, size_of_first_elimination_group);
273 |     min_position_per_residual[i] = position;
274 |     DCHECK_LE(position, size_of_first_elimination_group);
275 |     residual_blocks_per_e_block[position]++;
276 |   }
277 | 
278 |   // Run a cumulative sum on the histogram, to obtain offsets to the start of
279 |   // each histogram bucket (where each bucket is for the residuals for that
280 |   // E-block).
281 |   std::vector<int> offsets(size_of_first_elimination_group + 1);
282 |   std::partial_sum(residual_blocks_per_e_block.begin(),
283 |                    residual_blocks_per_e_block.end(),
284 |                    offsets.begin());
285 |   CHECK_EQ(offsets.back(), residual_blocks->size())
286 |       << "Congratulations, you found a Ceres bug! Please report this error "
287 |       << "to the developers.";
288 | 
289 |   CHECK(find(residual_blocks_per_e_block.begin(),
290 |              residual_blocks_per_e_block.end() - 1,
291 |              0) == residual_blocks_per_e_block.end() - 1)
292 |       << "Congratulations, you found a Ceres bug! Please report this error "
293 |       << "to the developers.";
294 | 
295 |   // Fill in each bucket with the residual blocks for its corresponding E block.
296 |   // Each bucket is individually filled from the back of the bucket to the front
297 |   // of the bucket. The filling order among the buckets is dictated by the
298 |   // residual blocks. This loop uses the offsets as counters; subtracting one
299 |   // from each offset as a residual block is placed in the bucket. When the
300 |   // filling is finished, the offset pointers should have shifted down one
301 |   // entry (this is verified below).
302 |   std::vector<ResidualBlock*> reordered_residual_blocks(
303 |       (*residual_blocks).size(), static_cast<ResidualBlock*>(nullptr));
304 |   for (int i = 0; i < residual_blocks->size(); ++i) {
305 |     int bucket = min_position_per_residual[i];
306 | 
307 |     // Decrement the cursor, which should now point at the next empty position.
308 |     offsets[bucket]--;
309 | 
310 |     // Sanity.
311 |     CHECK(reordered_residual_blocks[offsets[bucket]] == nullptr)
312 |         << "Congratulations, you found a Ceres bug! Please report this error "
313 |         << "to the developers.";
314 | 
315 |     reordered_residual_blocks[offsets[bucket]] = (*residual_blocks)[i];
316 |   }
317 | 
318 |   // Sanity check #1: The difference in bucket offsets should match the
319 |   // histogram sizes.
320 |   for (int i = 0; i < size_of_first_elimination_group; ++i) {
321 |     CHECK_EQ(residual_blocks_per_e_block[i], offsets[i + 1] - offsets[i])
322 |         << "Congratulations, you found a Ceres bug! Please report this error "
323 |         << "to the developers.";
324 |   }
325 |   // Sanity check #2: No nullptr's left behind.
326 |   for (auto* residual_block : reordered_residual_blocks) {
327 |     CHECK(residual_block != nullptr)
328 |         << "Congratulations, you found a Ceres bug! Please report this error "
329 |         << "to the developers.";
330 |   }
331 | 
332 |   // Now that the residuals are collected by E block, swap them in place.
333 |   swap(*program->mutable_residual_blocks(), reordered_residual_blocks);
334 |   return true;
335 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 4 (và 7 lệnh CHECK)

START → 1
1   CHECK_GE(size_of_first_elimination_group, 1)                   đúng → 2   sai → DỪNG
2   size_of_first_elimination_group + 1
    std::vector<ResidualBlock *> *residual_blocks = program->mutable_residual_blocks()
    residual_blocks->size()
    int i = 0                                                      → 3
3   vòng for, điều kiện: i < residual_blocks->size()               đúng → 4   sai → 8
4   ResidualBlock *residual_block = (*residual_blocks)[i]
    int position = MinParameterBlock(residual_block, size_of_first_elimination_group)
    min_position_per_residual[i] = position                        → 5
5   DCHECK_LE(position, size_of_first_elimination_group)           đúng → 6   sai → DỪNG
6   residual_blocks_per_e_block[position]++                        → 7
7   ++i                                                            → 3
8   size_of_first_elimination_group + 1                            → 9
9   CHECK_EQ(offsets.back(), residual_blocks->size())              đúng → 10   sai → DỪNG
10  0) == residual_blocks_per_e_block.end() - 1)                   đúng → 11   sai → DỪNG
11  vòng for, điều kiện: i < residual_blocks->size()               đúng → 12   sai → 15
12  int bucket = min_position_per_residual[i]
    offsets[bucket]--                                              → 13
13  CHECK(reordered_residual_blocks[offsets[bucket]] == nullptr)   đúng → 14   sai → DỪNG
14  ++i                                                            → 11
15  int i = 0                                                      → 16
16  vòng for, điều kiện: i < size_of_first_elimination_group       đúng → 17   sai → 19
17  CHECK_EQ(residual_blocks_per_e_block[i], offsets[i + 1] - offsets[i])   đúng → 18   sai → DỪNG
18  ++i                                                            → 16
19  for (auto *residual_block : reordered_residual_blocks)         đúng → 20   sai → 23
20  auto *residual_block                                           → 21
21  CHECK(residual_block != nullptr)                               đúng → 22   sai → DỪNG
22  ++ (bước tiếp của vòng for)                                    → 19
23  swap (ImplicitCastExpr, FunctionToPointerDecay, void (*)(vector<ResidualBlock *, allocator<ResidualBlock *> > &, vector<ResidualBlock *, allocator<ResidualBlock *> > &) noexcept(noexcept(__x.swap(__y))))(*program->mutable_residual_blocks(), reordered_residual_blocks)
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
#include "ceres/reorder_program.h"
#include "ceres/program.h"
#include "ceres/residual_block.h"
```

- Hàm gọi trực tiếp được.

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1410_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
