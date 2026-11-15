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

- Hàm: `Init(int num_eliminate_blocks, bool, const CompressedRowBlockStructure * bs)`, trả về `void`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::SchurEliminatorForOneFBlock` (class template)
- Vị trí: `internal/ceres/schur_eliminator.h`, dòng 386–428

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
386 |   void Init(int num_eliminate_blocks,
387 |             bool /*assume_full_rank_ete*/,
388 |             const CompressedRowBlockStructure* bs) override {
389 |     CHECK_GT(num_eliminate_blocks, 0)
390 |         << "SchurComplementSolver cannot be initialized with "
391 |         << "num_eliminate_blocks = 0.";
392 |     CHECK_EQ(bs->cols.size() - num_eliminate_blocks, 1);
393 | 
394 |     num_eliminate_blocks_ = num_eliminate_blocks;
395 |     const int num_row_blocks = bs->rows.size();
396 |     chunks_.clear();
397 |     int r = 0;
398 |     // Iterate over the row blocks of A, and detect the chunks. The
399 |     // matrix should already have been ordered so that all rows
400 |     // containing the same y block are vertically contiguous.
401 |     while (r < num_row_blocks) {
402 |       const int e_block_id = bs->rows[r].cells.front().block_id;
403 |       if (e_block_id >= num_eliminate_blocks_) {
404 |         break;
405 |       }
406 | 
407 |       chunks_.push_back(Chunk());
408 |       Chunk& chunk = chunks_.back();
409 |       chunk.num_rows = 0;
410 |       chunk.start = r;
411 |       // Add to the chunk until the first block in the row is
412 |       // different than the one in the first row for the chunk.
413 |       while (r + chunk.num_rows < num_row_blocks) {
414 |         const CompressedRow& row = bs->rows[r + chunk.num_rows];
415 |         if (row.cells.front().block_id != e_block_id) {
416 |           break;
417 |         }
418 |         ++chunk.num_rows;
419 |       }
420 |       r += chunk.num_rows;
421 |     }
422 | 
423 |     const Chunk& last_chunk = chunks_.back();
424 |     uneliminated_row_begins_ = last_chunk.start + last_chunk.num_rows;
425 |     e_t_e_inverse_matrices_.resize(kEBlockSize * kEBlockSize * chunks_.size());
426 |     std::fill(
427 |         e_t_e_inverse_matrices_.begin(), e_t_e_inverse_matrices_.end(), 0.0);
428 |   }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Ghi chú: đây là template – một số kiểu dữ liệu còn để trống, chỉ được điền khi dùng. CFG dưới đây dựng cho trường hợp SchurEliminatorForOneFBlock<2, 3, 6>.

Số điểm rẽ nhánh: 4 (và 2 lệnh CHECK)

START → 1
1   CHECK_GT(num_eliminate_blocks, 0)                              đúng → 2   sai → DỪNG
2   CHECK_EQ(bs->cols.size() - num_eliminate_blocks, 1)            đúng → 3   sai → DỪNG
3   num_eliminate_blocks_ = num_eliminate_blocks
    const int num_row_blocks = bs->rows.size()
    chunks_.clear()
    int r = 0                                                      → 4
4   while (r < num_row_blocks)                                     đúng → 5   sai → 8
5   const int e_block_id = bs->rows[r].cells.front().block_id      → 6
6   if (e_block_id >= num_eliminate_blocks_)                       đúng → 7   sai → 9
7   break                                                          → 8
8   const Chunk &last_chunk = chunks_.back()
    uneliminated_row_begins_ = last_chunk.start + last_chunk.num_rows
    e_t_e_inverse_matrices_.resize(3 * 3 * chunks_.size())         → END
9   chunks_.push_back(Chunk())
    Chunk &chunk = chunks_.back()
    chunk.num_rows = 0
    chunk.start = r                                                → 10
10  while (r + chunk.num_rows < num_row_blocks)                    đúng → 11   sai → 14
11  const CompressedRow &row = bs->rows[r + chunk.num_rows]        → 12
12  if (row.cells.front().block_id != e_block_id)                  đúng → 13   sai → 15
13  break                                                          → 14
14  r += chunk.num_rows                                            → 4
15  ++chunk.num_rows                                               → 10
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
#include "ceres/block_structure.h"
#include "ceres/schur_eliminator.h"
```

- Đây là method của class `ceres::internal::SchurEliminatorForOneFBlock`: tạo một object của class rồi gọi method trên object đó.
- Đây là template (khuôn mẫu): khi tạo object hoặc gọi hàm phải chọn kiểu cụ thể phù hợp.

Cách tạo object của class `SchurEliminatorForOneFBlock`:
- Class không tự khai báo constructor → tạo bằng constructor mặc định: `SchurEliminatorForOneFBlock obj;`

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u0774_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
