#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// SIGINT 핸들러 함수
void sigint_handler(int signo)
{
  printf("Ctrl+C 눌림!\n");
}

int main()
{
  // SIGINT 시그널 핸들러 설정
  signal(SIGINT, sigint_handler);

  printf("Ctrl+C를 눌러보세요...\n");

  while (1)
  {
    // 무한 루프
    sleep(1);
  }

  return 0;
}
