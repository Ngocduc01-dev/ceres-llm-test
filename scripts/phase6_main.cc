// Phase 6 – hàm main dùng chung cho mọi file test sinh ra (link cùng units/<id>/<id>_test.cc).
//
// Vì sao không dùng gmock_main có sẵn: khi CHECK sai (abort), segfault hoặc bị timeout kill,
// chương trình chết trước khi gcov kịp ghi file .gcda -> mất số liệu phủ của cả lần chạy.
// Ở đây mọi đường chết đều gọi __gcov_dump() trước rồi mới thoát, mã thoát cho biết lý do:
//   134 = CHECK / LOG(FATAL) của glog sai,  128 + số tín hiệu = crash (139 = SIGSEGV, 143 = SIGTERM / timeout).
#include <csignal>
#include <unistd.h>

#include "glog/logging.h"
#include "gtest/gtest.h"

extern "C" void __gcov_dump(void);

[[noreturn]] static void OnGlogFailure() {
  __gcov_dump();
  _exit(134);
}

static void OnSignal(int sig) {
  __gcov_dump();
  _exit(128 + sig);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  google::InstallFailureFunction(&OnGlogFailure);
  for (int sig : {SIGSEGV, SIGABRT, SIGTERM, SIGFPE, SIGBUS, SIGILL}) std::signal(sig, OnSignal);
  return RUN_ALL_TESTS();
}
