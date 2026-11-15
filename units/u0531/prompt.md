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

- Hàm: `PartitionRangeForParallelFor(int start, int end, int max_num_partitions, const CumulativeCostData* cumulative_cost_data, CumulativeCostFun&& cumulative_cost_fun)`, trả về `std::vector<int>`
- Loại: hàm template (hàm mẫu, kiểu dữ liệu được điền khi dùng)
- Namespace: `ceres::internal`
- Vị trí: `internal/ceres/partition_range_for_parallel_for.h`, dòng 94–147

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
 94 | template <typename CumulativeCostData, typename CumulativeCostFun>
 95 | std::vector<int> PartitionRangeForParallelFor(
 96 |     int start,
 97 |     int end,
 98 |     int max_num_partitions,
 99 |     const CumulativeCostData* cumulative_cost_data,
100 |     CumulativeCostFun&& cumulative_cost_fun) {
101 |   // Given maximal partition cost, it is possible to verify if it is admissible
102 |   // and obtain corresponding partition using MaxPartitionCostIsFeasible
103 |   // function. In order to find the lowest admissible value, a binary search
104 |   // over all potentially optimal cost values is being performed
105 |   const int cumulative_cost_last =
106 |       cumulative_cost_fun(cumulative_cost_data[end - 1]);
107 |   const int cumulative_cost_offset =
108 |       start ? cumulative_cost_fun(cumulative_cost_data[start - 1]) : 0;
109 |   const int total_cost = cumulative_cost_last - cumulative_cost_offset;
110 | 
111 |   // Minimal maximal partition cost is not smaller than the average
112 |   // We will use non-inclusive lower bound
113 |   int partition_cost_lower_bound = total_cost / max_num_partitions - 1;
114 |   // Minimal maximal partition cost is not larger than the total cost
115 |   // Upper bound is inclusive
116 |   int partition_cost_upper_bound = total_cost;
117 | 
118 |   std::vector<int> partition;
119 |   // Range partition corresponding to the latest evaluated upper bound.
120 |   // A single segment covering the whole input interval [start, end) corresponds
121 |   // to minimal maximal partition cost of total_cost.
122 |   std::vector<int> partition_upper_bound = {start, end};
123 |   // Binary search over partition cost, returning the lowest admissible cost
124 |   while (partition_cost_upper_bound - partition_cost_lower_bound > 1) {
125 |     partition.reserve(max_num_partitions + 1);
126 |     const int partition_cost =
127 |         partition_cost_lower_bound +
128 |         (partition_cost_upper_bound - partition_cost_lower_bound) / 2;
129 |     bool admissible = MaxPartitionCostIsFeasible(
130 |         start,
131 |         end,
132 |         max_num_partitions,
133 |         partition_cost,
134 |         cumulative_cost_offset,
135 |         cumulative_cost_data,
136 |         std::forward<CumulativeCostFun>(cumulative_cost_fun),
137 |         &partition);
138 |     if (admissible) {
139 |       partition_cost_upper_bound = partition_cost;
140 |       std::swap(partition, partition_upper_bound);
141 |     } else {
142 |       partition_cost_lower_bound = partition_cost;
143 |     }
144 |   }
145 | 
146 |   return partition_upper_bound;
147 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Ghi chú: đây là template – một số kiểu dữ liệu còn để trống, chỉ được điền khi dùng. CFG dưới đây dựng cho trường hợp PartitionRangeForParallelFor<CompressedList, (lambda at /work/ceres-solver/internal/ceres/block_sparse_matrix.cc:323:7)>.

Số điểm rẽ nhánh: 3

START → 1
1   const int cumulative_cost_last = cumulative_cost_fun(cumulative_cost_data[end - 1])   → 2
2   start ? ... : ...                                              đúng → 3   sai → 4
3   operator()                                                     → 4
4   const int cumulative_cost_offset = start ? cumulative_cost_fun(cumulative_cost_data[start - 1]) : 0
    const int total_cost = cumulative_cost_last - cumulative_cost_offset
    int partition_cost_lower_bound = total_cost / max_num_partitions - 1
    int partition_cost_upper_bound = total_cost
    {start, end}                                                   → 5
5   while (partition_cost_upper_bound - partition_cost_lower_bound > 1)   đúng → 6   sai → END
6   partition.reserve(max_num_partitions + 1)
    const int partition_cost = partition_cost_lower_bound + (partition_cost_upper_bound - partition_cost_lower_bound) / 2
    MaxPartitionCostIsFeasible (ImplicitCastExpr, FunctionToPointerDecay, _Bool (*)(int, int, int, int, int, const struct ceres::internal::CompressedList *, class (lambda at /work/ceres-solver/internal/ceres/block_sparse_matrix.cc:323:7) &&, std::vector<int> *))(start, end, max_num_partitions, partition_cost, cumulative_cost_offset, cumulative_cost_data, std::forward<(lambda at /work/ceres-solver/internal/ceres/block_sparse_matrix.cc:323:7)> (ImplicitCastExpr, BuiltinFnToFnPtr, class (lambda at /work/ceres-solver/internal/ceres/block_sparse_matrix.cc:323:7) &&(*)(typename std::remove_reference<class (lambda at /work/ceres-solver/internal/ceres/block_sparse_matrix.cc:323:7)>::type &) noexcept)(cumulative_cost_fun), &partition)
    bool admissible = MaxPartitionCostIsFeasible(start, end, max_num_partitions, partition_cost, cumulative_cost_offset, cumulative_cost_data, std::forward<(lambda at /work/ceres-solver/internal/ceres/block_sparse_matrix.cc:323:7)>(cumulative_cost_fun), &partition)   → 7
7   if (admissible)                                                đúng → 8   sai → 9
8   partition_cost_upper_bound = partition_cost
    std::swap (ImplicitCastExpr, FunctionToPointerDecay, void (*)(vector<int, allocator<int> > &, vector<int, allocator<int> > &) noexcept(noexcept(__x.swap(__y))))(partition, partition_upper_bound)   → 5
9   partition_cost_lower_bound = partition_cost                    → 5
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
#include "ceres/partition_range_for_parallel_for.h"
```

- Đây là template (khuôn mẫu): khi tạo object hoặc gọi hàm phải chọn kiểu cụ thể phù hợp.

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u0531_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
