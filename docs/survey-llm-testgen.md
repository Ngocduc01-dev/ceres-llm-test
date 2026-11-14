# Khảo sát: các công ty và nhóm nghiên cứu sinh unit test bằng LLM như thế nào

> Mục đích: trả lời câu hỏi **"chia prompt thế nào cho ~1500 unit"** dựa trên cách các hệ thống thật đang làm, thay vì tự nghĩ ra.
> Câu hỏi khảo sát chính: **mỗi lần gọi LLM xử lý cái gì** (1 hàm? 1 class? 1 file?), **đưa context gì vào**, **làm sao chạy được ở quy mô lớn**.

---

## 1. Hệ thống trong công nghiệp

| Hệ thống | Công ty | Ngôn ngữ | **1 lần gọi LLM xử lý** | Context đưa vào prompt | Vòng lặp / lọc | Quy mô, kết quả |
|---|---|---|---|---|---|---|
| **TestGen-LLM** (FSE 2024) [1] | Meta | Kotlin (Android) | **1 class**: class cần test + **file test có sẵn** của class đó → yêu cầu viết thêm test | `{class_under_test}`, `{existing_test_class}`; 4 khuôn prompt (`extend_test`, `extend_coverage`, `corner_cases`, `statement_to_complete`) | Lọc 4 tầng: build được → pass → chạy 5 lần không flaky → **tăng coverage**; bỏ test trùng | 1.979 class được xử lý, 196 class cải thiện (~10%); 73% đề xuất được kỹ sư chấp nhận; ~36.000 lượt sinh (trial) |
| **ACH** (FSE 2025) [2] | Meta | Kotlin | **1 class** + 1 lỗi giả (mutant) cụ thể → viết test bắt được lỗi đó | class, mutant | Lọc mutant tương đương bằng LLM | 10.795 class, 9.095 mutant, 571 test; 73% test được chấp nhận |
| **OSS-Fuzz-gen** [3][4] | Google | **C/C++** | **1 hàm** (hoặc vài hàm cùng project) → viết fuzz target (gọi hàm với **input ngẫu nhiên**) | 1 ví dụ fuzz target **có sẵn của chính project** (nhiều ví dụ hơn cho kết quả **kém hơn**), 2 ví dụ project khác, anti-pattern cần tránh | Compile lỗi → gửi lỗi cho LLM sửa (nhiều vòng); kiểm tra target có thật sự gọi hàm cần test; đo **coverage mới so với target cũ** | **Chọn hàm phủ thấp trước** (Fuzz Introspector); 14/31 project tăng coverage; tinyxml2 38% → 69% |
| **ASTER** [5] | IBM (đưa vào watsonx Code Assistant) | Java, Python | **1 hàm (focal method)** | Phân tích tĩnh: signature, chuỗi gọi hàm, dependency; mock dependency ngoài | Compile + chạy → sửa test lỗi; **bổ sung test cho đường đi chưa phủ** | Java EE: branch coverage cao hơn EvoSuite 10,6%; >70% trong 161 dev sẵn sàng dùng |
| **TestART** [6] | Huawei (tích hợp plugin nội bộ) | Java | 1 hàm | | Sinh và sửa xen kẽ nhiều vòng | |
| **LSPAI** (FSE 2025 industry) [7] | Tencent | Java, Go, Python | Plugin IDE (phần tóm tắt không nêu rõ đơn vị) | Lấy context qua **Language Server Protocol** (phân tích tĩnh) | | Line coverage vượt Copilot (Java +145%) |
| **Nghiên cứu SAP HANA** (ESEM 2026) [8] | SAP + TH Köln | **C++** (DBMS công nghiệp) | Sinh cả bộ test cho **1 component**; hoặc bổ sung bộ test có sẵn (amplification) | Source; source **+ header phụ thuộc** | Gửi lỗi compile cho LLM, tối đa 10 vòng | Vòng sửa tăng tỉ lệ compile 2–3× (tới 99%), **nhưng LLM bắt đầu viết test rỗng / xoá assertion để compile được**; thêm header phụ thuộc → mutation score +150% |

## 2. Nghiên cứu học thuật (để đối chiếu)

| Công trình | 1 lần gọi LLM xử lý | Điểm đáng học |
|---|---|---|
| TestPilot [9] | 1 hàm | Prompt = signature + thân hàm + ví dụ sử dụng; test lỗi → gửi lỗi lại |
| ChatUniTest [10] | 1 hàm | Chọn context theo giới hạn token ("adaptive focal context") |
| HITS [11] | **1 đoạn (slice) của hàm** | Hàm phức tạp → chia nhỏ, mỗi đoạn 1 lần gọi → tăng phủ nhánh |
| CoverUp [12] | Đoạn code **chưa phủ** | Dùng coverage chỉ cho LLM chỗ chưa phủ, lặp lại |
| CITYWALK [13] | (C++) | Phân tích **dependency toàn project** + kiến thức riêng của C++ |
| CATGen [14] | | Compile ổn định nhờ: dependency tường minh, **khung file test cố định**, dùng **phân tích tĩnh thay vì để LLM tự sửa** |

---

## 3. Rút ra: họ làm giống nhau ở đâu

1. **Không ai gom cả file nhiều thứ không liên quan vào 1 prompt.** Đơn vị phổ biến là **1 hàm** (Google, IBM, Huawei, học thuật) hoặc **1 class + file test của nó** (Meta).
2. **Quy mô lớn được giải quyết bằng tự động hoá + chọn lọc, không phải bằng giảm số lần gọi.** Meta chạy ~36.000 lượt sinh cho ~2.000 class; Google chạy theo từng hàm cho cả OSS-Fuzz. Số lần gọi LLM vài trăm – vài nghìn là bình thường khi chạy bằng script.
3. **Ưu tiên chỗ chưa phủ:** Google chọn hàm có coverage thấp trước; CoverUp/ASTER chỉ cho LLM đúng đoạn chưa phủ.
4. **Bám vào test có sẵn của project:** Meta mở rộng file test có sẵn; Google đưa 1 ví dụ của chính project (và cảnh báo: nhiều ví dụ hơn lại kém hơn).
5. **Context phụ thuộc tường minh là bắt buộc với C++:** SAP HANA và CITYWALK đều cho thấy thiếu header/dependency thì LLM bịa API, thiếu include, khởi tạo object sai.
6. **Vòng sửa lỗi compile có giới hạn** (Google, SAP: ~10 vòng) và **phải lọc kết quả**: build được, chạy được, **tăng coverage** (Meta). SAP cảnh báo: sửa nhiều vòng → LLM "ăn gian" viết test rỗng.

---

## 4. Áp dụng cho bài tập (Ceres 2.2.0, 1540 unit, C2)

> **Quyết định cuối của nhóm (sau khi đọc ý kiến của thầy trên discussion):** **1 prompt = 1 unit** – giống Google OSS-Fuzz-gen, IBM ASTER, Huawei TestART – thay vì gom theo class như Meta ở mục 4.1. Các ý còn lại của mục 4 (dùng test có sẵn làm mẫu, ưu tiên nhánh chưa phủ, lọc sau khi sinh, giới hạn vòng sửa) vẫn áp dụng. Xem `docs/PLAN.md`.

### 4.1. Đơn vị 1 prompt: **1 class** (theo Meta), hàm tự do: **1 file**

| | Áp dụng | Theo |
|---|---|---|
| **Đơn vị** | 1 prompt = 1 class cần test (hàm tự do: gom theo file nguồn). Class quá lớn (vượt ~15k token hoặc > ~60 nhánh) → chia theo nhóm method | Meta (class), HITS (chia nhỏ khi phức tạp) |
| **File có test sẵn** (117/208 file, **1068/1540 unit = 69%**) | Đưa file `*_test.cc` có sẵn vào prompt, yêu cầu **viết thêm test** cho các nhánh chưa phủ | Meta TestGen-LLM `extend_coverage` |
| **File chưa có test** (91 file, 472 unit) | Đưa **1 test mẫu** của file "hàng xóm" (cùng thư mục, cùng kiểu dữ liệu), yêu cầu viết file test mới | Google OSS-Fuzz-gen (1 ví dụ của chính project) |
| **Nhiệm vụ trong prompt** | Danh sách **nhánh chưa phủ** lấy từ `reports/baseline/coverage.json` (Phase 4) | CoverUp, ASTER, Google |
| **Context** | Context Phase 3, mục CLASS/TYPES/INCLUDES dùng chung 1 lần cho cả class | SAP HANA, CITYWALK |
| **Thứ tự** | Class có nhiều nhánh chưa phủ trước; trong cùng mức, theo `topo_level` từ dưới lên | Google (ưu tiên phủ thấp) |

→ Ước tính **~300 prompt** (đã mô phỏng trên context thật: gom theo class/file, giới hạn 15k token / 60 nhánh / 25 unit → 294 prompt). Chạy bằng script, không làm tay.

### 4.2. Sau khi sinh (tuần này: chạy 1 lượt; tuần 12–13: vòng sửa)

| Bước | Áp dụng | Theo |
|---|---|---|
| Lọc | Giữ test: compile được → chạy không crash/timeout → **tăng coverage**. Bỏ test trùng | Meta |
| Sửa lỗi compile | Gửi lỗi compile cho LLM, **tối đa 3–5 vòng**; lỗi lặp lại nhiều (thiếu include…) thì sửa bằng script/khuôn prompt chứ không để LLM sửa từng file | Google, SAP, CATGen |
| Chống "ăn gian" | Kiểm tra test có thật sự gọi unit cần test (không phải test rỗng) | Google, SAP |
| Phủ thêm | Nhánh vẫn chưa phủ → prompt mới chỉ chứa đúng các nhánh đó | CoverUp, ASTER |

### 4.3. Khác biệt cần ghi rõ trong báo cáo
- Meta/IBM có **test oracle** (assertion) – bài tập **không có EO** nên chỉ lọc theo compile/chạy/coverage, giống **Google OSS-Fuzz-gen** (fuzz target cũng không có expected output). Đây là hệ thống gần với bài tập nhất: C/C++, input ngẫu nhiên, đánh giá bằng coverage.
- Kết quả trên project mã nguồn mở có thể "đẹp" hơn thực tế vì LLM đã thấy code khi huấn luyện (SAP: LevelDB đạt 100% mutation score, SAP HANA chỉ 25%). Ceres là mã nguồn mở nổi tiếng → cần nêu điểm này.

---

## Nguồn

1. Alshahwan et al., *Automated Unit Test Improvement using Large Language Models at Meta*, FSE 2024 – [arXiv:2402.09171](https://arxiv.org/abs/2402.09171)
2. *Mutation-Guided LLM-based Test Generation at Meta*, FSE Companion 2025 – [arXiv:2501.12862](https://arxiv.org/abs/2501.12862)
3. Google OSS-Fuzz – [Fuzz target generation using LLMs](https://google.github.io/oss-fuzz/research/llms/target_generation/)
4. Google Security Blog – [AI-Powered Fuzzing: Breaking the Bug Hunting Barrier](https://security.googleblog.com/2023/08/ai-powered-fuzzing-breaking-bug-hunting.html)
5. IBM Research – [ASTER: LLM unit testing](https://research.ibm.com/blog/aster-llm-unit-testing)
6. *TestART: Improving LLM-based Unit Testing via Co-evolution of Automated Generation and Repair Iteration* – [arXiv:2408.03095](https://arxiv.org/abs/2408.03095)
7. *LSPAI: An IDE Plugin for LLM-Powered Multi-Language Unit Test Generation*, FSE 2025 Industry – [trang hội nghị](https://conf.researchr.org/details/fse-2025/fse-2025-industry-papers/12/LSPAI-An-IDE-Plugin-for-LLM-Powered-Multi-Language-Unit-Test-Generation-with-Languag)
8. Bekmyradov et al., *Evaluating LLM-Based Test Generation for a Large Industrial C++ Database System: A Case Study on SAP HANA*, ESEM 2026 – [DROPS](https://drops.dagstuhl.de/entities/document/10.4230/LIPIcs.ESEM.2026.95), [arXiv:2604.14437](https://arxiv.org/abs/2604.14437)
9. Schäfer et al., TestPilot, IEEE TSE 2024 – [arXiv:2302.06527](https://arxiv.org/abs/2302.06527)
10. Chen et al., ChatUniTest, FSE 2024 – [arXiv:2305.04764](https://arxiv.org/abs/2305.04764)
11. Wang et al., HITS – [arXiv:2408.11324](https://arxiv.org/abs/2408.11324)
12. Pizzorno & Berger, CoverUp – [arXiv:2403.16218](https://arxiv.org/abs/2403.16218)
13. Zhang et al., CITYWALK (C++) – [arXiv:2501.16155](https://arxiv.org/abs/2501.16155)
14. *Context Matters: Improving the Practical Reliability of LLM-Based Unit Test Generation* (CATGen) – [arXiv:2607.19682](https://arxiv.org/abs/2607.19682)
