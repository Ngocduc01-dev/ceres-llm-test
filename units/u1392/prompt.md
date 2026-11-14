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

- Hàm: `FullReport() const`, trả về `std::string`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::Solver::Summary`
- Vị trí: `internal/ceres/solver.cc`, dòng 852–1134

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
 852 | std::string Solver::Summary::FullReport() const {
 853 |   using internal::VersionString;
 854 | 
 855 |   // NOTE operator+ is not usable for concatenating a string and a string_view.
 856 |   std::string report =
 857 |       std::string{"\nSolver Summary (v "}.append(VersionString()) + ")\n\n";
 858 | 
 859 |   StringAppendF(&report, "%45s    %21s\n", "Original", "Reduced");
 860 |   StringAppendF(&report,
 861 |                 "Parameter blocks    % 25d% 25d\n",
 862 |                 num_parameter_blocks,
 863 |                 num_parameter_blocks_reduced);
 864 |   StringAppendF(&report,
 865 |                 "Parameters          % 25d% 25d\n",
 866 |                 num_parameters,
 867 |                 num_parameters_reduced);
 868 |   if (num_effective_parameters_reduced != num_parameters_reduced) {
 869 |     StringAppendF(&report,
 870 |                   "Effective parameters% 25d% 25d\n",
 871 |                   num_effective_parameters,
 872 |                   num_effective_parameters_reduced);
 873 |   }
 874 |   StringAppendF(&report,
 875 |                 "Residual blocks     % 25d% 25d\n",
 876 |                 num_residual_blocks,
 877 |                 num_residual_blocks_reduced);
 878 |   StringAppendF(&report,
 879 |                 "Residuals           % 25d% 25d\n",
 880 |                 num_residuals,
 881 |                 num_residuals_reduced);
 882 | 
 883 |   if (minimizer_type == TRUST_REGION) {
 884 |     // TRUST_SEARCH HEADER
 885 |     StringAppendF(
 886 |         &report, "\nMinimizer                 %19s\n", "TRUST_REGION");
 887 | 
 888 |     if (linear_solver_type_used == DENSE_NORMAL_CHOLESKY ||
 889 |         linear_solver_type_used == DENSE_SCHUR ||
 890 |         linear_solver_type_used == DENSE_QR) {
 891 |       const char* mixed_precision_suffix =
 892 |           (mixed_precision_solves_used ? "(Mixed Precision)" : "");
 893 |       StringAppendF(&report,
 894 |                     "\nDense linear algebra library  %15s %s\n",
 895 |                     DenseLinearAlgebraLibraryTypeToString(
 896 |                         dense_linear_algebra_library_type),
 897 |                     mixed_precision_suffix);
 898 |     }
 899 | 
 900 |     StringAppendF(&report,
 901 |                   "Trust region strategy     %19s",
 902 |                   TrustRegionStrategyTypeToString(trust_region_strategy_type));
 903 |     if (trust_region_strategy_type == DOGLEG) {
 904 |       if (dogleg_type == TRADITIONAL_DOGLEG) {
 905 |         StringAppendF(&report, " (TRADITIONAL)");
 906 |       } else {
 907 |         StringAppendF(&report, " (SUBSPACE)");
 908 |       }
 909 |     }
 910 | 
 911 |     const bool used_sparse_linear_algebra_library =
 912 |         linear_solver_type_used == SPARSE_NORMAL_CHOLESKY ||
 913 |         linear_solver_type_used == SPARSE_SCHUR ||
 914 |         linear_solver_type_used == CGNR ||
 915 |         (linear_solver_type_used == ITERATIVE_SCHUR &&
 916 |          (preconditioner_type_used == CLUSTER_JACOBI ||
 917 |           preconditioner_type_used == CLUSTER_TRIDIAGONAL));
 918 | 
 919 |     const bool linear_solver_ordering_required =
 920 |         linear_solver_type_used == SPARSE_SCHUR ||
 921 |         (linear_solver_type_used == ITERATIVE_SCHUR &&
 922 |          (preconditioner_type_used == CLUSTER_JACOBI ||
 923 |           preconditioner_type_used == CLUSTER_TRIDIAGONAL)) ||
 924 |         (linear_solver_type_used == CGNR && preconditioner_type_used == SUBSET);
 925 | 
 926 |     if (used_sparse_linear_algebra_library) {
 927 |       const char* mixed_precision_suffix =
 928 |           (mixed_precision_solves_used ? "(Mixed Precision)" : "");
 929 |       if (linear_solver_ordering_required) {
 930 |         StringAppendF(
 931 |             &report,
 932 |             "\nSparse linear algebra library %15s + %s %s\n",
 933 |             SparseLinearAlgebraLibraryTypeToString(
 934 |                 sparse_linear_algebra_library_type),
 935 |             LinearSolverOrderingTypeToString(linear_solver_ordering_type),
 936 |             mixed_precision_suffix);
 937 |       } else {
 938 |         StringAppendF(&report,
 939 |                       "\nSparse linear algebra library %15s %s\n",
 940 |                       SparseLinearAlgebraLibraryTypeToString(
 941 |                           sparse_linear_algebra_library_type),
 942 |                       mixed_precision_suffix);
 943 |       }
 944 |     }
 945 | 
 946 |     StringAppendF(&report, "\n");
 947 |     StringAppendF(&report, "%45s    %21s\n", "Given", "Used");
 948 |     StringAppendF(&report,
 949 |                   "Linear solver       %25s%25s\n",
 950 |                   LinearSolverTypeToString(linear_solver_type_given),
 951 |                   LinearSolverTypeToString(linear_solver_type_used));
 952 | 
 953 |     if (IsIterativeSolver(linear_solver_type_given)) {
 954 |       StringAppendF(&report,
 955 |                     "Preconditioner      %25s%25s\n",
 956 |                     PreconditionerTypeToString(preconditioner_type_given),
 957 |                     PreconditionerTypeToString(preconditioner_type_used));
 958 |     }
 959 | 
 960 |     if (preconditioner_type_used == CLUSTER_JACOBI ||
 961 |         preconditioner_type_used == CLUSTER_TRIDIAGONAL) {
 962 |       StringAppendF(
 963 |           &report,
 964 |           "Visibility clustering%24s%25s\n",
 965 |           VisibilityClusteringTypeToString(visibility_clustering_type),
 966 |           VisibilityClusteringTypeToString(visibility_clustering_type));
 967 |     }
 968 |     StringAppendF(&report,
 969 |                   "Threads             % 25d% 25d\n",
 970 |                   num_threads_given,
 971 |                   num_threads_used);
 972 | 
 973 |     std::string given;
 974 |     StringifyOrdering(linear_solver_ordering_given, &given);
 975 |     std::string used;
 976 |     StringifyOrdering(linear_solver_ordering_used, &used);
 977 |     StringAppendF(&report,
 978 |                   "Linear solver ordering %22s %24s\n",
 979 |                   given.c_str(),
 980 |                   used.c_str());
 981 |     if (IsSchurType(linear_solver_type_used)) {
 982 |       StringAppendF(&report,
 983 |                     "Schur structure        %22s %24s\n",
 984 |                     schur_structure_given.c_str(),
 985 |                     schur_structure_used.c_str());
 986 |     }
 987 | 
 988 |     if (inner_iterations_given) {
 989 |       StringAppendF(&report,
 990 |                     "Use inner iterations     %20s     %20s\n",
 991 |                     inner_iterations_given ? "True" : "False",
 992 |                     inner_iterations_used ? "True" : "False");
 993 |     }
 994 | 
 995 |     if (inner_iterations_used) {
 996 |       std::string given;
 997 |       StringifyOrdering(inner_iteration_ordering_given, &given);
 998 |       std::string used;
 999 |       StringifyOrdering(inner_iteration_ordering_used, &used);
1000 |       StringAppendF(&report,
1001 |                     "Inner iteration ordering %20s %24s\n",
1002 |                     given.c_str(),
1003 |                     used.c_str());
1004 |     }
1005 |   } else {
1006 |     // LINE_SEARCH HEADER
1007 |     StringAppendF(&report, "\nMinimizer                 %19s\n", "LINE_SEARCH");
1008 | 
1009 |     std::string line_search_direction_string;
1010 |     if (line_search_direction_type == LBFGS) {
1011 |       line_search_direction_string = StringPrintf("LBFGS (%d)", max_lbfgs_rank);
1012 |     } else if (line_search_direction_type == NONLINEAR_CONJUGATE_GRADIENT) {
1013 |       line_search_direction_string = NonlinearConjugateGradientTypeToString(
1014 |           nonlinear_conjugate_gradient_type);
1015 |     } else {
1016 |       line_search_direction_string =
1017 |           LineSearchDirectionTypeToString(line_search_direction_type);
1018 |     }
1019 | 
1020 |     StringAppendF(&report,
1021 |                   "Line search direction     %19s\n",
1022 |                   line_search_direction_string.c_str());
1023 | 
1024 |     const std::string line_search_type_string = StringPrintf(
1025 |         "%s %s",
1026 |         LineSearchInterpolationTypeToString(line_search_interpolation_type),
1027 |         LineSearchTypeToString(line_search_type));
1028 |     StringAppendF(&report,
1029 |                   "Line search type          %19s\n",
1030 |                   line_search_type_string.c_str());
1031 |     StringAppendF(&report, "\n");
1032 | 
1033 |     StringAppendF(&report, "%45s    %21s\n", "Given", "Used");
1034 |     StringAppendF(&report,
1035 |                   "Threads             % 25d% 25d\n",
1036 |                   num_threads_given,
1037 |                   num_threads_used);
1038 |   }
1039 | 
1040 |   StringAppendF(&report, "\nCost:\n");
1041 |   StringAppendF(&report, "Initial        % 30e\n", initial_cost);
1042 |   if (termination_type != FAILURE && termination_type != USER_FAILURE) {
1043 |     StringAppendF(&report, "Final          % 30e\n", final_cost);
1044 |     StringAppendF(&report, "Change         % 30e\n", initial_cost - final_cost);
1045 |   }
1046 | 
1047 |   StringAppendF(&report,
1048 |                 "\nMinimizer iterations         % 16d\n",
1049 |                 num_successful_steps + num_unsuccessful_steps);
1050 | 
1051 |   // Successful/Unsuccessful steps only matter in the case of the
1052 |   // trust region solver. Line search terminates when it encounters
1053 |   // the first unsuccessful step.
1054 |   if (minimizer_type == TRUST_REGION) {
1055 |     StringAppendF(&report,
1056 |                   "Successful steps               % 14d\n",
1057 |                   num_successful_steps);
1058 |     StringAppendF(&report,
1059 |                   "Unsuccessful steps             % 14d\n",
1060 |                   num_unsuccessful_steps);
1061 |   }
1062 |   if (inner_iterations_used) {
1063 |     StringAppendF(&report,
1064 |                   "Steps with inner iterations    % 14d\n",
1065 |                   num_inner_iteration_steps);
1066 |   }
1067 | 
1068 |   const bool line_search_used =
1069 |       (minimizer_type == LINE_SEARCH ||
1070 |        (minimizer_type == TRUST_REGION && is_constrained));
1071 | 
1072 |   if (line_search_used) {
1073 |     StringAppendF(&report,
1074 |                   "Line search steps              % 14d\n",
1075 |                   num_line_search_steps);
1076 |   }
1077 | 
1078 |   StringAppendF(&report, "\nTime (in seconds):\n");
1079 |   StringAppendF(
1080 |       &report, "Preprocessor        %25.6f\n", preprocessor_time_in_seconds);
1081 | 
1082 |   StringAppendF(&report,
1083 |                 "\n  Residual only evaluation %18.6f (%d)\n",
1084 |                 residual_evaluation_time_in_seconds,
1085 |                 num_residual_evaluations);
1086 |   if (line_search_used) {
1087 |     StringAppendF(&report,
1088 |                   "    Line search cost evaluation    %10.6f\n",
1089 |                   line_search_cost_evaluation_time_in_seconds);
1090 |   }
1091 |   StringAppendF(&report,
1092 |                 "  Jacobian & residual evaluation %12.6f (%d)\n",
1093 |                 jacobian_evaluation_time_in_seconds,
1094 |                 num_jacobian_evaluations);
1095 |   if (line_search_used) {
1096 |     StringAppendF(&report,
1097 |                   "    Line search gradient evaluation   %6.6f\n",
1098 |                   line_search_gradient_evaluation_time_in_seconds);
1099 |   }
1100 | 
1101 |   if (minimizer_type == TRUST_REGION) {
1102 |     StringAppendF(&report,
1103 |                   "  Linear solver       %23.6f (%d)\n",
1104 |                   linear_solver_time_in_seconds,
1105 |                   num_linear_solves);
1106 |   }
1107 | 
1108 |   if (inner_iterations_used) {
1109 |     StringAppendF(&report,
1110 |                   "  Inner iterations    %23.6f\n",
1111 |                   inner_iteration_time_in_seconds);
1112 |   }
1113 | 
1114 |   if (line_search_used) {
1115 |     StringAppendF(&report,
1116 |                   "  Line search polynomial minimization  %.6f\n",
1117 |                   line_search_polynomial_minimization_time_in_seconds);
1118 |   }
1119 | 
1120 |   StringAppendF(
1121 |       &report, "Minimizer           %25.6f\n\n", minimizer_time_in_seconds);
1122 | 
1123 |   StringAppendF(
1124 |       &report, "Postprocessor        %24.6f\n", postprocessor_time_in_seconds);
1125 | 
1126 |   StringAppendF(
1127 |       &report, "Total               %25.6f\n\n", total_time_in_seconds);
1128 | 
1129 |   StringAppendF(&report,
1130 |                 "Termination:        %25s (%s)\n",
1131 |                 TerminationTypeToString(termination_type),
1132 |                 message.c_str());
1133 |   return report;
1134 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 27

START → 1
1   StringAppendF(&report, "%45s    %21s\n", "Original", "Reduced")
    StringAppendF(&report, "Parameter blocks    % 25d% 25d\n", num_parameter_blocks, num_parameter_blocks_reduced)
    StringAppendF(&report, "Parameters          % 25d% 25d\n", num_parameters, num_parameters_reduced)   → 2
2   if (num_effective_parameters_reduced != num_parameters_reduced)   đúng → 3   sai → 4
3   StringAppendF(&report, "Effective parameters% 25d% 25d\n", num_effective_parameters, num_effective_parameters_reduced)   → 4
4   StringAppendF(&report, "Residual blocks     % 25d% 25d\n", num_residual_blocks, num_residual_blocks_reduced)
    StringAppendF(&report, "Residuals           % 25d% 25d\n", num_residuals, num_residuals_reduced)   → 5
5   if (minimizer_type == TRUST_REGION)                            đúng → 6   sai → 61
6   StringAppendF(&report, "\nMinimizer                 %19s\n", "TRUST_REGION")   → 7
7   if (linear_solver_type_used == DENSE_NORMAL_CHOLESKY || linear_solver_type_used == DENSE_SCHUR || linear_solver_type_used == DENSE_QR)   đúng → 8   sai → 10
8   mixed_precision_solves_used ? ... : ...                        đúng → 9   sai → 9
9   const char *mixed_precision_suffix = (mixed_precision_solves_used ? "(Mixed Precision)" : "")
    StringAppendF(&report, "\nDense linear algebra library  %15s %s\n", DenseLinearAlgebraLibraryTypeToString(dense_linear_algebra_library_type), mixed_precision_suffix)   → 10
10  StringAppendF(&report, "Trust region strategy     %19s", TrustRegionStrategyTypeToString(trust_region_strategy_type))   → 11
11  if (trust_region_strategy_type == DOGLEG)                      đúng → 12   sai → 14
12  if (dogleg_type == TRADITIONAL_DOGLEG)                         đúng → 13   sai → 60
13  StringAppendF(&report, " (TRADITIONAL)")                       → 14
14  const bool used_sparse_linear_algebra_library = linear_solver_type_used == SPARSE_NORMAL_CHOLESKY || linear_solver_type_used == SPARSE_SCHUR || linear_solver_type_used == CGNR || (linear_solver_type_used == ITERATIVE_SCHUR && (preconditioner_type_used == CLUSTER_JACOBI || preconditioner_type_used == CLUSTER_TRIDIAGONAL))   → 15
15  const bool linear_solver_ordering_required = linear_solver_type_used == SPARSE_SCHUR || (linear_solver_type_used == ITERATIVE_SCHUR && (preconditioner_type_used == CLUSTER_JACOBI || preconditioner_type_used == CLUSTER_TRIDIAGONAL)) || (linear_solver_type_used == CGNR && preconditioner_type_used == SUBSET)   → 16
16  if (used_sparse_linear_algebra_library)                        đúng → 17   sai → 21
17  mixed_precision_solves_used ? ... : ...                        đúng → 18   sai → 18
18  const char *mixed_precision_suffix = (mixed_precision_solves_used ? "(Mixed Precision)" : "")   → 19
19  if (linear_solver_ordering_required)                           đúng → 20   sai → 59
20  StringAppendF(&report, "\nSparse linear algebra library %15s + %s %s\n", SparseLinearAlgebraLibraryTypeToString(sparse_linear_algebra_library_type), LinearSolverOrderingTypeToString(linear_solver_ordering_type), mixed_precision_suffix)   → 21
21  StringAppendF(&report, "\n")
    StringAppendF(&report, "%45s    %21s\n", "Given", "Used")
    StringAppendF(&report, "Linear solver       %25s%25s\n", LinearSolverTypeToString(linear_solver_type_given), LinearSolverTypeToString(linear_solver_type_used))   → 22
22  if (IsIterativeSolver(linear_solver_type_given))               đúng → 23   sai → 24
23  StringAppendF(&report, "Preconditioner      %25s%25s\n", PreconditionerTypeToString(preconditioner_type_given), PreconditionerTypeToString(preconditioner_type_used))   → 24
24  if (preconditioner_type_used == CLUSTER_JACOBI || preconditioner_type_used == CLUSTER_TRIDIAGONAL)   đúng → 25   sai → 26
25  StringAppendF(&report, "Visibility clustering%24s%25s\n", VisibilityClusteringTypeToString(visibility_clustering_type), VisibilityClusteringTypeToString(visibility_clustering_type))   → 26
26  StringAppendF(&report, "Threads             % 25d% 25d\n", num_threads_given, num_threads_used)
    StringifyOrdering(linear_solver_ordering_given, &given)
    StringifyOrdering(linear_solver_ordering_used, &used)
    StringAppendF(&report, "Linear solver ordering %22s %24s\n", given.c_str(), used.c_str())   → 27
27  if (IsSchurType(linear_solver_type_used))                      đúng → 28   sai → 29
28  StringAppendF(&report, "Schur structure        %22s %24s\n", schur_structure_given.c_str(), schur_structure_used.c_str())   → 29
29  if (inner_iterations_given)                                    đúng → 30   sai → 33
30  inner_iterations_given ? ... : ...                             đúng → 31   sai → 31
31  inner_iterations_used ? ... : ...                              đúng → 32   sai → 32
32  StringAppendF(&report, "Use inner iterations     %20s     %20s\n", inner_iterations_given ? "True" : "False", inner_iterations_used ? "True" : "False")   → 33
33  if (inner_iterations_used)                                     đúng → 34   sai → 35
34  StringifyOrdering(inner_iteration_ordering_given, &given)
    StringifyOrdering(inner_iteration_ordering_used, &used)
    StringAppendF(&report, "Inner iteration ordering %20s %24s\n", given.c_str(), used.c_str())   → 35
35  StringAppendF(&report, "\nCost:\n")
    StringAppendF(&report, "Initial        % 30e\n", initial_cost)   → 36
36  if (termination_type != FAILURE && termination_type != USER_FAILURE)   đúng → 37   sai → 38
37  StringAppendF(&report, "Final          % 30e\n", final_cost)
    StringAppendF(&report, "Change         % 30e\n", initial_cost - final_cost)   → 38
38  StringAppendF(&report, "\nMinimizer iterations         % 16d\n", num_successful_steps + num_unsuccessful_steps)   → 39
39  if (minimizer_type == TRUST_REGION)                            đúng → 40   sai → 41
40  StringAppendF(&report, "Successful steps               % 14d\n", num_successful_steps)
    StringAppendF(&report, "Unsuccessful steps             % 14d\n", num_unsuccessful_steps)   → 41
41  if (inner_iterations_used)                                     đúng → 42   sai → 43
42  StringAppendF(&report, "Steps with inner iterations    % 14d\n", num_inner_iteration_steps)   → 43
43  const bool line_search_used = (minimizer_type == LINE_SEARCH || (minimizer_type == TRUST_REGION && is_constrained))   → 44
44  if (line_search_used)                                          đúng → 45   sai → 46
45  StringAppendF(&report, "Line search steps              % 14d\n", num_line_search_steps)   → 46
46  StringAppendF(&report, "\nTime (in seconds):\n")
    StringAppendF(&report, "Preprocessor        %25.6f\n", preprocessor_time_in_seconds)
    StringAppendF(&report, "\n  Residual only evaluation %18.6f (%d)\n", residual_evaluation_time_in_seconds, num_residual_evaluations)   → 47
47  if (line_search_used)                                          đúng → 48   sai → 49
48  StringAppendF(&report, "    Line search cost evaluation    %10.6f\n", line_search_cost_evaluation_time_in_seconds)   → 49
49  StringAppendF(&report, "  Jacobian & residual evaluation %12.6f (%d)\n", jacobian_evaluation_time_in_seconds, num_jacobian_evaluations)   → 50
50  if (line_search_used)                                          đúng → 51   sai → 52
51  StringAppendF(&report, "    Line search gradient evaluation   %6.6f\n", line_search_gradient_evaluation_time_in_seconds)   → 52
52  if (minimizer_type == TRUST_REGION)                            đúng → 53   sai → 54
53  StringAppendF(&report, "  Linear solver       %23.6f (%d)\n", linear_solver_time_in_seconds, num_linear_solves)   → 54
54  if (inner_iterations_used)                                     đúng → 55   sai → 56
55  StringAppendF(&report, "  Inner iterations    %23.6f\n", inner_iteration_time_in_seconds)   → 56
56  if (line_search_used)                                          đúng → 57   sai → 58
57  StringAppendF(&report, "  Line search polynomial minimization  %.6f\n", line_search_polynomial_minimization_time_in_seconds)   → 58
58  StringAppendF(&report, "Minimizer           %25.6f\n\n", minimizer_time_in_seconds)
    StringAppendF(&report, "Postprocessor        %24.6f\n", postprocessor_time_in_seconds)
    StringAppendF(&report, "Total               %25.6f\n\n", total_time_in_seconds)
    StringAppendF(&report, "Termination:        %25s (%s)\n", TerminationTypeToString(termination_type), message.c_str())   → END
59  StringAppendF(&report, "\nSparse linear algebra library %15s %s\n", SparseLinearAlgebraLibraryTypeToString(sparse_linear_algebra_library_type), mixed_precision_suffix)   → 21
60  StringAppendF(&report, " (SUBSPACE)")                          → 14
61  StringAppendF(&report, "\nMinimizer                 %19s\n", "LINE_SEARCH")   → 62
62  if (line_search_direction_type == LBFGS)                       đúng → 63   sai → 65
63  operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    line_search_direction_string = StringPrintf("LBFGS (%d)", max_lbfgs_rank)   → 64
64  StringAppendF(&report, "Line search direction     %19s\n", line_search_direction_string.c_str())
    StringPrintf("%s %s", LineSearchInterpolationTypeToString(line_search_interpolation_type), LineSearchTypeToString(line_search_type))
    StringAppendF(&report, "Line search type          %19s\n", line_search_type_string.c_str())
    StringAppendF(&report, "\n")
    StringAppendF(&report, "%45s    %21s\n", "Given", "Used")
    StringAppendF(&report, "Threads             % 25d% 25d\n", num_threads_given, num_threads_used)   → 35
65  if (line_search_direction_type == NONLINEAR_CONJUGATE_GRADIENT)   đúng → 66   sai → 67
66  line_search_direction_string = NonlinearConjugateGradientTypeToString(nonlinear_conjugate_gradient_type)   → 64
67  line_search_direction_string = LineSearchDirectionTypeToString(line_search_direction_type)   → 64
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
```

- Đây là method của class `ceres::Solver::Summary`: tạo một object của class rồi gọi method trên object đó.

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1392_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
