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

- Hàm: `CreateSchurComplementGraph(const std::vector<std::set<int>> & visibility)`, trả về `std::unique_ptr<WeightedGraph<int>>`
- Loại: hàm tự do (không thuộc class)
- Namespace: `ceres::internal`
- Vị trí: `internal/ceres/visibility.cc`, dòng 76–145

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
 76 | std::unique_ptr<WeightedGraph<int>> CreateSchurComplementGraph(
 77 |     const std::vector<std::set<int>>& visibility) {
 78 |   const time_t start_time = time(nullptr);
 79 |   // Compute the number of e_blocks/point blocks. Since the visibility
 80 |   // set for each e_block/camera contains the set of e_blocks/points
 81 |   // visible to it, we find the maximum across all visibility sets.
 82 |   int num_points = 0;
 83 |   for (const auto& visible : visibility) {
 84 |     if (!visible.empty()) {
 85 |       num_points = std::max(num_points, (*visible.rbegin()) + 1);
 86 |     }
 87 |   }
 88 | 
 89 |   // Invert the visibility. The input is a camera->point mapping,
 90 |   // which tells us which points are visible in which
 91 |   // cameras. However, to compute the sparsity structure of the Schur
 92 |   // Complement efficiently, its better to have the point->camera
 93 |   // mapping.
 94 |   std::vector<std::set<int>> inverse_visibility(num_points);
 95 |   for (int i = 0; i < visibility.size(); i++) {
 96 |     const std::set<int>& visibility_set = visibility[i];
 97 |     for (int v : visibility_set) {
 98 |       inverse_visibility[v].insert(i);
 99 |     }
100 |   }
101 | 
102 |   // Map from camera pairs to number of points visible to both cameras
103 |   // in the pair.
104 |   std::unordered_map<std::pair<int, int>, int, pair_hash> camera_pairs;
105 | 
106 |   // Count the number of points visible to each camera/f_block pair.
107 |   for (const auto& inverse_visibility_set : inverse_visibility) {
108 |     for (auto camera1 = inverse_visibility_set.begin();
109 |          camera1 != inverse_visibility_set.end();
110 |          ++camera1) {
111 |       auto camera2 = camera1;
112 |       for (++camera2; camera2 != inverse_visibility_set.end(); ++camera2) {
113 |         ++(camera_pairs[std::make_pair(*camera1, *camera2)]);
114 |       }
115 |     }
116 |   }
117 | 
118 |   auto graph = std::make_unique<WeightedGraph<int>>();
119 | 
120 |   // Add vertices and initialize the pairs for self edges so that self
121 |   // edges are guaranteed. This is needed for the Canonical views
122 |   // algorithm to work correctly.
123 |   static constexpr double kSelfEdgeWeight = 1.0;
124 |   for (int i = 0; i < visibility.size(); ++i) {
125 |     graph->AddVertex(i);
126 |     graph->AddEdge(i, i, kSelfEdgeWeight);
127 |   }
128 | 
129 |   // Add an edge for each camera pair.
130 |   for (const auto& camera_pair_count : camera_pairs) {
131 |     const int camera1 = camera_pair_count.first.first;
132 |     const int camera2 = camera_pair_count.first.second;
133 |     const int count = camera_pair_count.second;
134 |     DCHECK_NE(camera1, camera2);
135 |     // Static cast necessary for Windows.
136 |     const double weight =
137 |         static_cast<double>(count) /
138 |         (sqrt(static_cast<double>(visibility[camera1].size() *
139 |                                   visibility[camera2].size())));
140 |     graph->AddEdge(camera1, camera2, weight);
141 |   }
142 | 
143 |   VLOG(2) << "Schur complement graph time: " << (time(nullptr) - start_time);
144 |   return graph;
145 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 10 (và 1 lệnh CHECK)

START → 1
1   const time_t start_time = time(nullptr)
    int num_points = 0                                             → 2
2   for (const auto &visible : visibility)                         đúng → 3   sai → 7
3   const auto &visible                                            → 4
4   if (!visible.empty())                                          đúng → 5   sai → 6
5   num_points = std::max(num_points, (* visible.rbegin()) + 1)    → 6
6   ++ (bước tiếp của vòng for)                                    → 2
7   int i = 0                                                      → 8
8   vòng for, điều kiện: i < visibility.size()                     đúng → 9   sai → 14
9   const std::set<int> &visibility_set = visibility[i]            → 10
10  for (int v : visibility_set)                                   đúng → 11   sai → 13
11  int v
    inverse_visibility[v].insert(i)                                → 12
12  ++ (bước tiếp của vòng for)                                    → 10
13  i++                                                            → 8
14  for (const auto &inverse_visibility_set : inverse_visibility)   đúng → 15   sai → 23
15  const auto &inverse_visibility_set
    inverse_visibility_set.begin()                                 → 16
16  vòng for, điều kiện: camera1 != inverse_visibility_set.end()   đúng → 17   sai → 22
17  ++ camera2                                                     → 18
18  vòng for, điều kiện: camera2 != inverse_visibility_set.end()   đúng → 19   sai → 21
19  ++(camera_pairs[std::make_pair(* camera1, * camera2)])         → 20
20  ++ camera2                                                     → 18
21  ++ camera1                                                     → 16
22  ++ (bước tiếp của vòng for)                                    → 14
23  static init kSelfEdgeWeight                                    đúng → 24   sai → 33
24  int i = 0                                                      → 25
25  vòng for, điều kiện: i < visibility.size()                     đúng → 26   sai → 28
26  graph->AddVertex(i)
    graph->AddEdge(i, i, kSelfEdgeWeight)                          → 27
27  ++i                                                            → 25
28  for (const auto &camera_pair_count : camera_pairs)             đúng → 29   sai → END
29  const auto &camera_pair_count
    const int camera1 = camera_pair_count.first.first
    const int camera2 = camera_pair_count.first.second
    const int count = camera_pair_count.second                     → 30
30  DCHECK_NE(camera1, camera2)                                    đúng → 31   sai → DỪNG
31  const double weight = static_cast<double>(count) / (sqrt(static_cast<double>(visibility[camera1].size() * visibility[camera2].size())))
    graph->AddEdge(camera1, camera2, weight)                       → 32
32  ++ (bước tiếp của vòng for)                                    → 28
33  static constexpr double kSelfEdgeWeight = 1.                   → 24
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
#include "ceres/visibility.h"
#include "ceres/graph.h"
#include "ceres/pair_hash.h"
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u0784_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
