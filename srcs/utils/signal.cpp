#include "utils.hpp"

void SigIntHanlder(int signalNum) {
  std::cout << signalNum << " : 서버를 종료합니다." << std::endl;

  // 필요하면 후속처리 파트 넣기
  exit(1);
  return;
}

void initSignal() {
  signal(SIGINT, SigIntHanlder);
  return;
}