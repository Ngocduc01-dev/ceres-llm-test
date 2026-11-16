# Phase 6 – lượt 1: compile, chạy, đo phủ

Trang tổng quan độ phủ: [gen_coverage.html](gen_coverage.html). Cách đo: `docs/phase6-guide.md`.

| Trạng thái | Số unit |
|---|---|
| `ok` | 467 |
| `compile_fail` | 32 |
| `link_fail` | 4 |

**Test case** (trong 467 unit chạy được): pass 528, fail 0, check_fail 17, crash 14, timeout 0

**Độ phủ trên các dòng của unit** (gộp các unit chạy được):

- C1 (dòng): 1228/1297 = 95%
- C2 (nhánh, đếm theo điểm rẽ nhánh như CFG): 107/115 = 93%; điểm rẽ nhánh không đo được (uncheckable): 0
- Unit có nhánh: 47; phủ đủ 100% nhánh: 41; tổng nhánh đo được khớp số nhánh CFG: 42/47

| Unit | Trạng thái | Test (pass/tổng) | C1 | C2 | Nhánh CFG | Nhánh chưa phủ / lỗi đầu tiên |
|---|---|---|---|---|---|---|
| u0001 | ok | 1/1 | 100% | – |  |  |
| u0002 | ok | 1/1 | 100% | – | 0 |  |
| u0003 | ok | 1/1 | 100% | – |  |  |
| u0004 | compile_fail | /0 | – | – | 0 | include/ceres/autodiff_manifold.h:161:22: error: ‘struct ceres::{anonymous}::TestEuclideanFunctor’ has no member named ‘ |
| u0005 | compile_fail | /0 | – | – | 0 | include/ceres/autodiff_manifold.h:161:22: error: ‘struct ceres::{anonymous}::EuclideanFunctor’ has no member named ‘Plus |
| u0006 | compile_fail | /0 | – | – | 0 | include/ceres/autodiff_manifold.h:161:22: error: ‘struct {anonymous}::EuclideanFunctor’ has no member named ‘Plus’ |
| u0007 | ok | 1/1 | 100% | – | 0 |  |
| u0008 | ok | 1/1 | 100% | – | 0 |  |
| u0009 | ok | 1/1 | 100% | – |  |  |
| u0010 | ok | 1/1 | 100% | – | 0 |  |
| u0011 | ok | 1/1 | 100% | – | 0 |  |
| u0012 | ok | 1/1 | 100% | – | 0 |  |
| u0013 | ok | 1/1 | 100% | – | 0 |  |
| u0014 | ok | 1/1 | 100% | – | 0 |  |
| u0015 | ok | 1/1 | 100% | – | 0 |  |
| u0016 | ok | 1/1 | 100% | – | 0 |  |
| u0017 | ok | 1/1 | 100% | – |  |  |
| u0018 | ok | 1/1 | 100% | – |  |  |
| u0019 | ok | 1/1 | 100% | – |  |  |
| u0020 | ok | 1/1 | 100% | – | 0 |  |
| u0021 | ok | 1/1 | 100% | – | 0 |  |
| u0022 | ok | 1/1 | 100% | – | 0 |  |
| u0023 | ok | 1/1 | 100% | – | 0 |  |
| u0024 | ok | 1/1 | 100% | – | 0 |  |
| u0025 | ok | 1/1 | 100% | – | 2 |  |
| u0026 | ok | 1/1 | 100% | – | 0 |  |
| u0027 | ok | 1/1 | 100% | – | 0 |  |
| u0028 | ok | 1/1 | 100% | – | 0 |  |
| u0029 | ok | 1/1 | 100% | – |  |  |
| u0030 | ok | 1/1 | 100% | – | 0 |  |
| u0031 | ok | 1/1 | 100% | – | 0 |  |
| u0032 | ok | 1/1 | 100% | – | 0 |  |
| u0033 | ok | 1/1 | 100% | – | 0 |  |
| u0034 | ok | 1/1 | 100% | – | 0 |  |
| u0035 | ok | 1/1 | 100% | – | 0 |  |
| u0036 | ok | 1/1 | 100% | – | 0 |  |
| u0037 | ok | 1/1 | 100% | – | 0 |  |
| u0038 | ok | 1/1 | 100% | – |  |  |
| u0039 | ok | 1/1 | 100% | – |  |  |
| u0040 | ok | 1/1 | 100% | – | 0 |  |
| u0041 | ok | 1/1 | 100% | – | 0 |  |
| u0042 | ok | 1/1 | 100% | – | 0 |  |
| u0043 | ok | 1/1 | 100% | – | 0 |  |
| u0044 | ok | 1/1 | 100% | – | 0 |  |
| u0045 | ok | 1/1 | 100% | – | 0 |  |
| u0046 | ok | 1/1 | 100% | – | 0 |  |
| u0047 | ok | 1/1 | 100% | – | 0 |  |
| u0048 | ok | 1/1 | 100% | – | 0 |  |
| u0049 | ok | 1/1 | 100% | – | 0 |  |
| u0050 | ok | 1/1 | 100% | – | 0 |  |
| u0051 | ok | 1/1 | 0% | – | 0 |  |
| u0052 | ok | 1/1 | 0% | – | 0 |  |
| u0053 | ok | 1/1 | 100% | – | 0 |  |
| u0054 | compile_fail | /0 | – | – | 0 | /usr/include/c++/14/sstream:457:7: error: ‘struct std::__cxx11::basic_stringbuf<_CharT, _Traits, _Alloc>::__xfer_bufptrs |
| u0055 | compile_fail | /0 | – | – | 0 | /usr/include/c++/14/any:371:7: error: ‘struct std::any::_Manager_internal<_Tp>’ redeclared with different access |
| u0056 | ok | 1/1 | 100% | – | 0 |  |
| u0057 | ok | 1/1 | 100% | – | 0 |  |
| u0058 | ok | 1/1 | 100% | – | 0 |  |
| u0059 | ok | 1/1 | 100% | – | 4 |  |
| u0060 | ok | 1/1 | 100% | – | 0 |  |
| u0061 | ok | 1/1 | 100% | – | 0 |  |
| u0062 | ok | 1/1 | 100% | – | 0 |  |
| u0063 | ok | 1/1 | 100% | – | 0 |  |
| u0064 | ok | 1/1 | 100% | – | 0 |  |
| u0065 | compile_fail | /0 | – | – | 0 | units/u0065/u0065_test.cc:29:51: error: call of overloaded ‘VariadicEvaluateImpl<ceres::internal::ParameterDims<false, 2 |
| u0066 | ok | 1/1 | 100% | – | 0 |  |
| u0067 | ok | 1/1 | 100% | – | 0 |  |
| u0068 | ok | 1/1 | 100% | – | 0 |  |
| u0069 | ok | 1/1 | 100% | – | 0 |  |
| u0070 | ok | 1/1 | 100% | – | 0 |  |
| u0071 | ok | 1/1 | 100% | – | 0 |  |
| u0072 | ok | 1/1 | 100% | – | 0 |  |
| u0073 | ok | 1/1 | 100% | – | 0 |  |
| u0074 | ok | 1/1 | 100% | – | 0 |  |
| u0075 | ok | 1/1 | 100% | – | 0 |  |
| u0076 | ok | 1/1 | 100% | – | 0 |  |
| u0077 | ok | 1/1 | 100% | – | 0 |  |
| u0078 | ok | 1/1 | 100% | – | 0 |  |
| u0079 | ok | 1/1 | 100% | – | 0 |  |
| u0080 | ok | 1/1 | 100% | – | 0 |  |
| u0081 | ok | 1/1 | 100% | – | 0 |  |
| u0082 | ok | 1/1 | 100% | – | 0 |  |
| u0083 | ok | 1/1 | 100% | – | 0 |  |
| u0084 | ok | 1/1 | 100% | – | 0 |  |
| u0085 | ok | 1/1 | 100% | – | 0 |  |
| u0086 | ok | 1/1 | 100% | – | 0 |  |
| u0087 | ok | 1/1 | 100% | – | 0 |  |
| u0088 | ok | 1/1 | 100% | – | 0 |  |
| u0089 | ok | 1/1 | 100% | – | 0 |  |
| u0090 | ok | 1/1 | 100% | – | 0 |  |
| u0091 | ok | 1/1 | 100% | – | 0 |  |
| u0092 | ok | 1/1 | 100% | – | 0 |  |
| u0093 | ok | 1/1 | 100% | – | 0 |  |
| u0094 | ok | 1/1 | 100% | – | 0 |  |
| u0095 | ok | 1/1 | 100% | – | 0 |  |
| u0096 | ok | 1/1 | 100% | – | 0 |  |
| u0097 | ok | 1/1 | 100% | – | 0 |  |
| u0098 | ok | 1/1 | 100% | – | 0 |  |
| u0099 | ok | 1/1 | 100% | – | 0 |  |
| u0100 | ok | 1/1 | 100% | – | 0 |  |
| u0101 | ok | 1/1 | 100% | – | 0 |  |
| u0102 | ok | 1/1 | 100% | – | 0 |  |
| u0103 | ok | 1/1 | 100% | – | 0 |  |
| u0104 | ok | 1/1 | 100% | – | 0 |  |
| u0105 | ok | 1/1 | 100% | – | 0 |  |
| u0106 | ok | 1/1 | 100% | – | 0 |  |
| u0107 | ok | 1/1 | 100% | – | 0 |  |
| u0108 | ok | 1/1 | 100% | – | 0 |  |
| u0109 | ok | 1/1 | 100% | – | 0 |  |
| u0110 | ok | 1/1 | 100% | – | 0 |  |
| u0111 | ok | 1/1 | 100% | – | 0 |  |
| u0112 | ok | 1/1 | 100% | – | 0 |  |
| u0113 | ok | 1/1 | 100% | – | 0 |  |
| u0114 | ok | 1/1 | 100% | – | 0 |  |
| u0115 | ok | 1/1 | 100% | – | 0 |  |
| u0116 | ok | 1/1 | 100% | – | 0 |  |
| u0117 | ok | 1/1 | 100% | – | 0 |  |
| u0118 | ok | 1/1 | 100% | – | 0 |  |
| u0119 | ok | 1/1 | 100% | – | 0 |  |
| u0120 | ok | 1/1 | 100% | – | 0 |  |
| u0121 | ok | 1/1 | 100% | – | 0 |  |
| u0122 | ok | 1/1 | 100% | – | 0 |  |
| u0123 | ok | 1/1 | 100% | – | 0 |  |
| u0124 | ok | 1/1 | 100% | – | 0 |  |
| u0125 | ok | 1/1 | 67% | – | 0 |  |
| u0126 | ok | 1/1 | 100% | – | 0 |  |
| u0127 | ok | 1/1 | 100% | – | 0 |  |
| u0128 | ok | 1/1 | 100% | – | 0 |  |
| u0129 | ok | 1/1 | 100% | – | 0 |  |
| u0130 | ok | 1/1 | 100% | – | 0 |  |
| u0131 | ok | 1/1 | 100% | – | 0 |  |
| u0132 | ok | 1/1 | 100% | – | 0 |  |
| u0133 | ok | 1/1 | 100% | – | 0 |  |
| u0134 | ok | 1/1 | 100% | – | 0 |  |
| u0135 | ok | 1/1 | 100% | – | 0 |  |
| u0136 | ok | 1/1 | 100% | – | 0 |  |
| u0137 | ok | 1/1 | 100% | – | 0 |  |
| u0138 | ok | 1/1 | 100% | – | 0 |  |
| u0139 | ok | 1/1 | 100% | – | 0 |  |
| u0140 | ok | 1/1 | 100% | – | 0 |  |
| u0141 | ok | 1/1 | 100% | – | 0 |  |
| u0142 | ok | 1/1 | 100% | – | 0 |  |
| u0143 | ok | 1/1 | 100% | – | 0 |  |
| u0144 | ok | 1/1 | 100% | – |  |  |
| u0145 | ok | 1/1 | 100% | – |  |  |
| u0146 | ok | 1/1 | 100% | – |  |  |
| u0147 | ok | 1/1 | 100% | – |  |  |
| u0148 | ok | 1/1 | 100% | – | 0 |  |
| u0149 | ok | 1/1 | 100% | – | 0 |  |
| u0150 | ok | 1/1 | 100% | – | 0 |  |
| u0151 | ok | 1/1 | 100% | – |  |  |
| u0152 | ok | 1/1 | 100% | – |  |  |
| u0153 | ok | 1/1 | 100% | – |  |  |
| u0154 | ok | 1/1 | 100% | – |  |  |
| u0155 | ok | 1/1 | 100% | – |  |  |
| u0156 | ok | 1/1 | 100% | – |  |  |
| u0157 | ok | 1/1 | 100% | – |  |  |
| u0158 | ok | 1/1 | 100% | – |  |  |
| u0159 | ok | 1/1 | 100% | – |  |  |
| u0160 | ok | 1/1 | 100% | – |  |  |
| u0161 | ok | 1/1 | 100% | – |  |  |
| u0162 | ok | 1/1 | 100% | – |  |  |
| u0163 | compile_fail | /0 | – | – |  | include/ceres/jet.h:1383:71: error: ‘max_digits10’ is not a member of ‘Eigen::NumTraits<double>’ |
| u0164 | ok | 1/1 | 100% | – |  |  |
| u0165 | ok | 1/1 | 100% | – |  |  |
| u0166 | ok | 1/1 | 100% | – | 0 |  |
| u0167 | ok | 1/1 | 100% | – | 0 |  |
| u0168 | ok | 1/1 | 100% | – | 0 |  |
| u0169 | ok | 1/1 | 100% | – | 0 |  |
| u0170 | ok | 1/1 | 100% | – | 0 |  |
| u0171 | ok | 1/1 | 100% | – | 0 |  |
| u0172 | ok | 1/1 | 100% | – | 0 |  |
| u0173 | ok | 1/1 | 100% | – | 0 |  |
| u0174 | ok | 1/1 | 100% | – | 0 |  |
| u0175 | ok | 1/1 | 100% | – | 0 |  |
| u0176 | ok | 1/1 | 100% | – | 0 |  |
| u0177 | ok | 1/1 | 100% | – | 0 |  |
| u0178 | ok | 1/1 | 100% | – | 0 |  |
| u0179 | ok | 1/1 | 100% | – | 0 |  |
| u0180 | ok | 1/1 | 100% | – | 0 |  |
| u0181 | ok | 1/1 | 100% | – | 0 |  |
| u0182 | ok | 1/1 | 100% | – | 0 |  |
| u0183 | ok | 1/1 | 100% | – | 0 |  |
| u0184 | ok | 1/1 | 100% | – | 0 |  |
| u0185 | ok | 1/1 | 100% | – | 0 |  |
| u0186 | ok | 1/1 | 100% | – | 0 |  |
| u0187 | ok | 1/1 | 100% | – | 0 |  |
| u0188 | ok | 1/1 | 100% | – | 0 |  |
| u0189 | ok | 1/1 | 100% | – |  |  |
| u0190 | ok | 1/1 | 100% | – | 0 |  |
| u0191 | ok | 1/1 | 100% | – |  |  |
| u0192 | ok | 1/1 | 100% | – | 0 |  |
| u0193 | ok | 1/1 | 100% | – | 0 |  |
| u0194 | ok | 1/1 | 100% | – | 0 |  |
| u0195 | ok | 1/1 | 100% | – | 0 |  |
| u0196 | ok | 1/1 | 100% | – | 0 |  |
| u0197 | compile_fail | /0 | – | – |  | include/ceres/ordered_groups.h:185:61: error: invalid initialization of reference of type ‘const std::map<int, int, std: |
| u0198 | compile_fail | /0 | – | – | 0 | units/u0198/u0198_test.cc:9:41: error: ‘SphereManifold’ was not declared in this scope |
| u0199 | ok | 1/1 | 100% | – | 0 |  |
| u0200 | compile_fail | /0 | – | – | 0 | units/u0200/u0200_test.cc:12:62: error: no matching function for call to ‘ceres::SubsetManifold::SubsetManifold(int, std |
| u0201 | compile_fail | /0 | – | – | 0 | units/u0201/u0201_test.cc:16:58: error: no matching function for call to ‘ceres::SubsetManifold::SubsetManifold(int, std |
| u0202 | compile_fail | /0 | – | – | 0 | units/u0202/u0202_test.cc:12:61: error: no matching function for call to ‘ceres::SubsetManifold::SubsetManifold(int, std |
| u0203 | ok | 1/1 | 100% | – | 0 |  |
| u0204 | ok | 1/1 | 100% | – | 0 |  |
| u0205 | ok | 3/3 | 100% | – | 6 |  |
| u0206 | ok | 1/1 | 100% | – | 0 |  |
| u0207 | ok | 1/1 | 100% | – | 0 |  |
| u0208 | ok | 1/1 | 100% | – | 0 |  |
| u0209 | ok | 1/1 | 100% | – | 0 |  |
| u0210 | ok | 1/1 | 100% | – | 0 |  |
| u0211 | ok | 1/1 | 100% | – | 0 |  |
| u0212 | ok | 1/1 | 100% | – | 0 |  |
| u0213 | ok | 1/1 | 100% | – |  |  |
| u0214 | ok | 1/1 | 100% | – | 0 |  |
| u0215 | ok | 1/1 | 100% | – | 0 |  |
| u0216 | ok | 1/1 | 100% | – | 0 |  |
| u0217 | ok | 1/1 | 100% | – | 0 |  |
| u0218 | ok | 1/1 | 100% | – | 0 |  |
| u0219 | ok | 1/1 | 100% | – | 0 |  |
| u0220 | ok | 1/1 | 100% | – | 0 |  |
| u0221 | ok | 1/1 | 100% | – | 0 |  |
| u0222 | ok | 1/1 | 100% | – | 0 |  |
| u0223 | ok | 1/1 | 100% | – | 0 |  |
| u0224 | ok | 1/1 | 100% | – | 0 |  |
| u0225 | ok | 1/1 | 100% | – | 0 |  |
| u0226 | ok | 1/1 | 100% | – | 0 |  |
| u0227 | ok | 1/1 | – | – | 0 |  |
| u0228 | ok | 1/1 | 100% | – | 0 |  |
| u0229 | ok | 1/1 | 100% | – | 0 |  |
| u0230 | ok | 1/1 | 100% | – | 0 |  |
| u0231 | ok | 1/1 | 100% | – | 0 |  |
| u0232 | ok | 1/1 | 100% | – | 0 |  |
| u0233 | ok | 1/1 | 100% | – | 0 |  |
| u0234 | ok | 1/1 | 100% | – | 0 |  |
| u0235 | ok | 1/1 | 100% | – | 0 |  |
| u0236 | ok | 1/1 | 100% | – | 0 |  |
| u0237 | ok | 1/1 | – | – | 0 |  |
| u0238 | ok | 1/1 | 100% | – | 0 |  |
| u0239 | ok | 1/1 | – | – | 0 |  |
| u0240 | ok | 1/1 | 100% | – | 0 |  |
| u0241 | ok | 1/1 | 100% | – | 0 |  |
| u0242 | ok | 1/1 | 100% | – | 0 |  |
| u0243 | compile_fail | /0 | – | – | 0 | units/u0243/u0243_test.cc:6:3: error: ‘ceres_init’ was not declared in this scope |
| u0244 | compile_fail | /0 | – | – | 0 | units/u0244/u0244_test.cc:23:3: error: ‘ceres’ has not been declared |
| u0245 | compile_fail | /0 | – | – | 0 | units/u0245/u0245_test.cc:7:3: error: ‘ceres_loss_function_t’ was not declared in this scope; did you mean ‘cookie_close |
| u0246 | compile_fail | /0 | – | – | 0 | units/u0246/u0246_test.cc:22:3: error: ‘CallbackLossFunction’ was not declared in this scope |
| u0247 | ok | 1/1 | 100% | – | 0 |  |
| u0248 | ok | 1/1 | 100% | – | 0 |  |
| u0249 | ok | 1/1 | 100% | – | 0 |  |
| u0250 | ok | 1/1 | 100% | – | 0 |  |
| u0251 | ok | 1/1 | 100% | – | 0 |  |
| u0252 | ok | 1/1 | – | – | 0 |  |
| u0253 | ok | 1/1 | 100% | – | 0 |  |
| u0254 | ok | 1/1 | 100% | – | 0 |  |
| u0255 | ok | 1/1 | 100% | – | 0 |  |
| u0256 | ok | 1/1 | 100% | – | 0 |  |
| u0257 | ok | 1/1 | 100% | – | 0 |  |
| u0258 | ok | 1/1 | 100% | – | 0 |  |
| u0259 | ok | 1/1 | 100% | – | 0 |  |
| u0260 | ok | 1/1 | 100% | – | 0 |  |
| u0261 | ok | 1/1 | 100% | – | 0 |  |
| u0262 | ok | 1/1 | 100% | – | 0 |  |
| u0263 | ok | 1/1 | 100% | – | 0 |  |
| u0264 | ok | 1/1 | 100% | – | 0 |  |
| u0265 | ok | 1/1 | 100% | – | 0 |  |
| u0266 | ok | 1/1 | 100% | – | 0 |  |
| u0267 | ok | 1/1 | 100% | – | 0 |  |
| u0268 | ok | 1/1 | 100% | – | 0 |  |
| u0269 | ok | 1/1 | 100% | – | 0 |  |
| u0270 | ok | 1/1 | 100% | – | 0 |  |
| u0271 | ok | 1/1 | 100% | – | 0 |  |
| u0272 | ok | 1/1 | 100% | – | 0 |  |
| u0273 | ok | 1/1 | 100% | – | 0 |  |
| u0274 | ok | 0/1 | 0% | – | 0 |  |
| u0275 | ok | 1/1 | 100% | – | 0 |  |
| u0276 | ok | 0/1 | – | – | 0 |  |
| u0277 | compile_fail | /0 | – | – | 0 | units/u0277/u0277_test.cc:14:77: error: invalid use of incomplete type ‘class ceres::internal::DenseIterativeRefiner’ |
| u0278 | ok | 0/1 | – | – | 0 |  |
| u0279 | ok | 1/1 | 100% | – | 0 |  |
| u0280 | ok | 1/1 | 100% | – | 0 |  |
| u0281 | ok | 0/1 | 0% | – | 0 |  |
| u0282 | ok | 0/1 | 0% | – | 0 |  |
| u0283 | ok | 0/1 | 0% | – | 0 |  |
| u0284 | ok | 0/1 | 0% | – | 0 |  |
| u0285 | ok | 1/1 | 100% | – | 0 |  |
| u0286 | ok | 0/1 | 0% | – | 0 |  |
| u0287 | ok | 1/1 | 100% | – | 0 |  |
| u0288 | ok | 0/1 | 0% | – | 0 |  |
| u0289 | ok | 0/1 | – | – | 0 |  |
| u0290 | ok | 0/1 | – | – | 0 |  |
| u0291 | ok | 1/1 | 100% | – | 0 |  |
| u0292 | ok | 0/1 | – | – | 0 |  |
| u0293 | ok | 0/1 | – | – | 0 |  |
| u0294 | ok | 1/1 | – | – | 0 |  |
| u0295 | ok | 1/1 | 100% | – | 0 |  |
| u0296 | ok | 0/1 | – | – | 0 |  |
| u0297 | ok | 1/1 | 100% | – | 0 |  |
| u0298 | ok | 1/1 | 100% | – | 0 |  |
| u0299 | ok | 1/1 | 100% | – | 0 |  |
| u0300 | ok | 1/1 | 100% | – | 0 |  |
| u0301 | ok | 1/1 | 100% | – | 0 |  |
| u0302 | ok | 1/1 | 100% | – | 0 |  |
| u0303 | ok | 1/1 | 100% | – | 0 |  |
| u0304 | ok | 1/1 | 100% | – | 0 |  |
| u0305 | ok | 1/1 | 100% | – | 0 |  |
| u0306 | ok | 1/1 | 100% | – | 0 |  |
| u0307 | ok | 1/1 | 100% | – | 0 |  |
| u0308 | ok | 1/1 | 100% | – | 0 |  |
| u0309 | ok | 1/1 | 100% | – | 0 |  |
| u0310 | ok | 1/1 | 100% | – | 0 |  |
| u0311 | ok | 1/1 | 100% | – | 0 |  |
| u0312 | ok | 1/1 | 100% | – | 0 |  |
| u0313 | ok | 1/1 | 100% | – | 0 |  |
| u0314 | ok | 1/1 | 100% | – | 0 |  |
| u0315 | compile_fail | /0 | – | – | 0 | units/u0315/u0315_test.cc:10:25: error: ‘struct ceres::internal::InnerProductComputer::ProductTerm’ is private within th |
| u0316 | ok | 1/1 | 100% | – | 0 |  |
| u0317 | ok | 1/1 | 100% | – | 0 |  |
| u0318 | ok | 1/1 | 100% | – | 0 |  |
| u0319 | ok | 1/1 | 100% | – | 0 |  |
| u0320 | ok | 1/1 | 100% | – | 0 |  |
| u0321 | ok | 0/1 | 0% | – | 0 |  |
| u0322 | ok | 1/1 | 100% | – | 0 |  |
| u0323 | ok | 0/1 | 0% | – | 0 |  |
| u0324 | compile_fail | /0 | – | – | 0 | /usr/include/c++/14/bits/unique_ptr.h:91:23: error: invalid application of ‘sizeof’ to incomplete type ‘ceres::internal: |
| u0325 | compile_fail | /0 | – | – | 0 | /usr/include/c++/14/bits/unique_ptr.h:91:23: error: invalid application of ‘sizeof’ to incomplete type ‘ceres::internal: |
| u0326 | compile_fail | /0 | – | – | 0 | /usr/include/c++/14/bits/unique_ptr.h:91:23: error: invalid application of ‘sizeof’ to incomplete type ‘ceres::internal: |
| u0327 | ok | 1/1 | 100% | – | 0 |  |
| u0328 | ok | 1/1 | 100% | – | 0 |  |
| u0329 | ok | 1/1 | – | – | 0 |  |
| u0330 | ok | 1/1 | 100% | – | 0 |  |
| u0331 | ok | 1/1 | 100% | 1/1 | 0 |  |
| u0332 | ok | 1/1 | 100% | – | 0 |  |
| u0333 | ok | 1/1 | 100% | – | 0 |  |
| u0334 | ok | 1/1 | 100% | – | 0 |  |
| u0335 | ok | 1/1 | 100% | – | 0 |  |
| u0336 | ok | 1/1 | 100% | – | 0 |  |
| u0337 | ok | 1/1 | 100% | – | 0 |  |
| u0338 | ok | 1/1 | 100% | – | 0 |  |
| u0339 | ok | 1/1 | 100% | – | 0 |  |
| u0340 | ok | 1/1 | 100% | – | 0 |  |
| u0341 | ok | 1/1 | 100% | – | 0 |  |
| u0342 | ok | 1/1 | 100% | – | 0 |  |
| u0343 | ok | 1/1 | 100% | – | 0 |  |
| u0344 | ok | 1/1 | 100% | – | 0 |  |
| u0345 | ok | 1/1 | 100% | – | 0 |  |
| u0346 | ok | 1/1 | 100% | – | 0 |  |
| u0347 | ok | 1/1 | 100% | – | 0 |  |
| u0348 | ok | 1/1 | 100% | – | 0 |  |
| u0349 | ok | 1/1 | 100% | – | 0 |  |
| u0350 | ok | 1/1 | 100% | – | 0 |  |
| u0351 | ok | 1/1 | 100% | – | 0 |  |
| u0352 | ok | 1/1 | 100% | – | 0 |  |
| u0353 | ok | 1/1 | 100% | – | 0 |  |
| u0354 | compile_fail | /0 | – | – | 0 | internal/ceres/parallel_invoke.h:165:6: error: variable or field ‘ParallelInvoke’ declared void |
| u0355 | compile_fail | /0 | – | – | 0 | internal/ceres/parallel_invoke.h:165:6: error: variable or field ‘ParallelInvoke’ declared void |
| u0356 | ok | 1/1 | 100% | – | 0 |  |
| u0357 | ok | 1/1 | 100% | – | 0 |  |
| u0358 | ok | 1/1 | 100% | – | 0 |  |
| u0359 | ok | 1/1 | 100% | – | 0 |  |
| u0360 | ok | 1/1 | 100% | – | 0 |  |
| u0361 | ok | 1/1 | 100% | – | 0 |  |
| u0362 | ok | 1/1 | 100% | – | 0 |  |
| u0363 | ok | 1/1 | 100% | – | 0 |  |
| u0364 | ok | 1/1 | 100% | – | 0 |  |
| u0365 | ok | 1/1 | 100% | – | 0 |  |
| u0366 | ok | 1/1 | 100% | – | 0 |  |
| u0367 | ok | 1/1 | 100% | – | 0 |  |
| u0368 | ok | 1/1 | 100% | – | 0 |  |
| u0369 | ok | 1/1 | 100% | – | 0 |  |
| u0370 | ok | 1/1 | 100% | – | 0 |  |
| u0371 | ok | 1/1 | 100% | – | 0 |  |
| u0372 | ok | 1/1 | 100% | – | 0 |  |
| u0373 | link_fail | /0 | – | – | 0 | /usr/bin/ld: /work/build-cov/gen/u0373/test.o: in function `ceres::internal::PartitionedMatrixViewNumColBlocksE_TC1_P1_R |
| u0374 | ok | 1/1 | 100% | – | 0 |  |
| u0375 | ok | 1/1 | 100% | – | 0 |  |
| u0376 | link_fail | /0 | – | – | 0 | /usr/bin/ld: /work/build-cov/gen/u0376/test.o: in function `ceres::internal::PartitionedMatrixViewNumColsF_TC1_ReturnNum |
| u0377 | link_fail | /0 | – | – | 0 | /usr/bin/ld: /work/build-cov/gen/u0377/test.o: in function `ceres::internal::PartitionedMatrixViewETest_ECColsPartitionP |
| u0378 | link_fail | /0 | – | – | 0 | /usr/bin/ld: /work/build-cov/gen/u0378/test.o: in function `ceres::internal::PartitionedMatrixViewFColsPartition_Returns |
| u0379 | ok | 1/1 | 100% | – | 0 |  |
| u0380 | ok | 1/1 | 100% | – | 0 |  |
| u0381 | ok | 1/1 | 100% | – | 0 |  |
| u0382 | ok | 1/1 | 100% | – | 0 |  |
| u0383 | ok | 1/1 | 100% | – | 0 |  |
| u0384 | ok | 1/1 | 100% | – | 0 |  |
| u0385 | ok | 1/1 | 100% | – | 0 |  |
| u0386 | ok | 1/1 | 100% | – | 0 |  |
| u0387 | ok | 1/1 | 100% | – | 0 |  |
| u0388 | ok | 1/1 | 100% | – | 0 |  |
| u0389 | ok | 1/1 | 100% | – | 0 |  |
| u0390 | ok | 1/1 | 100% | – | 0 |  |
| u0391 | ok | 1/1 | 100% | – | 0 |  |
| u0392 | ok | 1/1 | 100% | – | 0 |  |
| u0393 | ok | 1/1 | 100% | – | 0 |  |
| u0394 | ok | 1/1 | 100% | – | 0 |  |
| u0395 | ok | 1/1 | 100% | – | 0 |  |
| u0396 | ok | 1/1 | 100% | – | 0 |  |
| u0397 | ok | 1/1 | 100% | – | 0 |  |
| u0398 | ok | 1/1 | 100% | – | 0 |  |
| u0399 | ok | 1/1 | 100% | – | 0 |  |
| u0400 | compile_fail | /0 | – | – | 0 | internal/ceres/program_evaluator.h:109:19: error: ‘SparseMatrix’ has not been declared |
| u0401 | ok | 1/1 | 100% | – | 0 |  |
| u0402 | ok | 1/1 | 100% | – | 0 |  |
| u0403 | ok | 1/1 | 100% | – | 0 |  |
| u0404 | ok | 0/1 | 0% | – | 0 |  |
| u0405 | ok | 1/1 | 100% | – | 0 |  |
| u0406 | ok | 1/1 | 100% | – | 0 |  |
| u0407 | ok | 1/1 | 100% | – | 0 |  |
| u0408 | ok | 0/1 | 0% | – | 0 |  |
| u0409 | ok | 1/1 | 100% | – | 0 |  |
| u0410 | ok | 1/1 | 100% | – | 0 |  |
| u0411 | ok | 1/1 | 100% | – | 0 |  |
| u0412 | ok | 1/1 | 100% | – | 0 |  |
| u0413 | ok | 1/1 | 100% | – | 0 |  |
| u0414 | ok | 1/1 | 100% | – | 0 |  |
| u0415 | compile_fail | /0 | – | – | 0 | /usr/include/c++/14/bits/unique_ptr.h:91:23: error: invalid application of ‘sizeof’ to incomplete type ‘ceres::internal: |
| u0416 | ok | 0/1 | 0% | – | 0 |  |
| u0417 | ok | 1/1 | 100% | – | 0 |  |
| u0418 | ok | 1/1 | 100% | – | 0 |  |
| u0419 | ok | 0/1 | 0% | – | 0 |  |
| u0420 | compile_fail | /0 | – | – | 0 | internal/ceres/suitesparse.h:284:23: error: variable ‘ceres::internal::CERES_NO_EXPORT ceres::internal::SuiteSparse’ has |
| u0421 | compile_fail | /0 | – | – | 0 | internal/ceres/suitesparse.h:284:23: error: variable ‘ceres::internal::CERES_NO_EXPORT ceres::internal::SuiteSparse’ has |
| u0422 | ok | 1/1 | 100% | – | 0 |  |
| u0423 | ok | 1/1 | 100% | – | 0 |  |
| u0424 | ok | 1/1 | 100% | – | 0 |  |
| u0425 | ok | 1/1 | 100% | – | 0 |  |
| u0426 | ok | 1/1 | 100% | – | 0 |  |
| u0427 | ok | 1/1 | 100% | – | 0 |  |
| u0428 | ok | 1/1 | 100% | – | 0 |  |
| u0429 | ok | 1/1 | 100% | – | 0 |  |
| u0430 | ok | 1/1 | 100% | – | 0 |  |
| u0431 | ok | 1/1 | 100% | – | 0 |  |
| u0432 | ok | 1/1 | 100% | – | 0 |  |
| u0433 | ok | 1/1 | 100% | – | 0 |  |
| u0434 | ok | 0/1 | 0% | – | 0 |  |
| u0435 | ok | 1/1 | 100% | – | 0 |  |
| u0436 | ok | 2/2 | 100% | 2/2 | 2 |  |
| u0437 | ok | 2/2 | 100% | 2/2 | 2 |  |
| u0438 | compile_fail | /0 | – | – | 2 | include/ceres/autodiff_manifold.h:161:22: error: ‘struct ceres::{anonymous}::EuclideanFunctorN<5>’ has no member named ‘ |
| u0439 | compile_fail | /0 | – | – | 2 | units/u0439/u0439_test.cc:12:10: error: ‘Jet’ is not a member of ‘ceres’ |
| u0440 | ok | 1/1 | 100% | – | 0 |  |
| u0441 | ok | 2/2 | 100% | 2/2 | 2 |  |
| u0442 | ok | 1/1 | 100% | 2/2 | 2 |  |
| u0443 | ok | 2/2 | 100% | 2/2 | 2 |  |
| u0444 | ok | 2/2 | 100% | 2/2 | 2 |  |
| u0445 | ok | 1/1 | 100% | – | 0 |  |
| u0446 | ok | 1/1 | 100% | – | 0 |  |
| u0447 | ok | 2/2 | 100% | 2/2 | 2 |  |
| u0448 | ok | 6/6 | 100% | 2/2 | 2 |  |
| u0449 | ok | 1/1 | 100% | 2/2 | 2 |  |
| u0450 | ok | 1/1 | 100% | 2/2 | 2 |  |
| u0451 | ok | 2/2 | 100% | 2/2 | 2 |  |
| u0452 | ok | 2/2 | 100% | 2/2 | 2 |  |
| u0453 | ok | 2/2 | 100% | 2/2 | 2 |  |
| u0454 | ok | 2/2 | 100% | 2/2 | 2 |  |
| u0455 | ok | 2/2 | 100% | 2/2 | 2 |  |
| u0456 | ok | 2/2 | 100% | 2/2 | 2 |  |
| u0457 | ok | 2/2 | 100% | 2/2 | 2 |  |
| u0458 | ok | 2/2 | 100% | 2/2 | 2 |  |
| u0459 | ok | 0/2 | 28% | 0/2 | 2 | dòng 324: đúng/sai |
| u0460 | ok | 1/1 | 100% | – | 0 |  |
| u0461 | ok | 1/1 | 100% | – | 0 |  |
| u0462 | ok | 1/1 | 100% | – | 0 |  |
| u0463 | ok | 2/2 | 100% | 2/2 | 2 |  |
| u0464 | ok | 6/6 | 100% | 2/2 | 2 |  |
| u0465 | ok | 2/2 | 100% | 2/2 | 2 |  |
| u0466 | ok | 0/1 | 0% | – | 0 |  |
| u0467 | ok | 0/1 | 0% | – | 0 |  |
| u0468 | compile_fail | /0 | – | – | 2 | units/u0468/u0468_test.cc:12:7: error: expected ‘;’ before ‘bfgs’ |
| u0469 | ok | 2/2 | 100% | 2/2 | 2 |  |
| u0470 | ok | 2/2 | 100% | 2/2 | 4 |  |
| u0471 | ok | 2/2 | 100% | 2/2 | 2 |  |
| u0472 | ok | 2/2 | 100% | 2/2 | 2 |  |
| u0473 | ok | 1/1 | 100% | – | 0 |  |
| u0474 | ok | 1/1 | 80% | 1/2 | 2 | dòng 76: sai |
| u0475 | ok | 1/1 | 80% | 1/2 |  | dòng 104: đúng |
| u0476 | ok | 0/1 | 75% | – | 0 |  |
| u0477 | ok | 2/2 | 100% | 2/2 | 2 |  |
| u0478 | compile_fail | /0 | – | – | 0 | internal/ceres/parallel_invoke.h:165:6: error: variable or field ‘ParallelInvoke’ declared void |
| u0479 | ok | 2/2 | 100% | 2/2 | 2 |  |
| u0480 | ok | 2/2 | 100% | – | 2 |  |
| u0481 | ok | 2/2 | 100% | – | 2 |  |
| u0482 | ok | 2/2 | 100% | 2/2 | 2 |  |
| u0483 | ok | 2/2 | 100% | 2/2 | 2 |  |
| u0484 | ok | 2/2 | 100% | 2/2 | 2 |  |
| u0485 | ok | 1/1 | 75% | – | 0 |  |
| u0486 | ok | 6/6 | 100% | 2/2 | 2 |  |
| u0487 | ok | 6/6 | 100% | 2/2 | 2 |  |
| u0488 | ok | 6/6 | 100% | 2/2 | 2 |  |
| u0489 | ok | 2/2 | 100% | 2/2 | 2 |  |
| u0490 | ok | 7/7 | 100% | 2/2 | 2 |  |
| u0491 | ok | 1/1 | 100% | – | 0 |  |
| u0492 | ok | 2/2 | 88% | 1/2 | 2 | dòng 58: đúng |
| u0493 | compile_fail | /0 | – | – | 4 | include/ceres/autodiff_manifold.h:190:20: error: ‘const struct ceres::{anonymous}::TestPlusFunctor<1>’ has no member nam |
| u0494 | ok | 2/2 | 100% | 4/4 | 4 |  |
| u0495 | ok | 6/6 | 100% | 2/2 | 2 |  |
| u0496 | ok | 3/3 | 100% | – | 4 |  |
| u0497 | ok | 6/6 | 100% | 2/2 | 4 |  |
| u0498 | ok | 0/4 | 26% | 0/2 | 4 | dòng 355: đúng/sai |
| u0499 | ok | 1/1 | 100% | – | 0 |  |
| u0500 | ok | 1/1 | 100% | – |  |  |
| u0553 | ok | 5/6 | 92% | 11/12 | 12 | dòng 229: đúng |
| u1119 | ok | 6/6 | 95% | 6/6 | 6 |  |
| u1199 | ok | 4/4 | 100% | 8/8 | 8 |  |
