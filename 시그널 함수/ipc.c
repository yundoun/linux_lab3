#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// 시그널 핸들러 함수
void sigusr1_handler(int signo)
{
  printf("자식 프로세스: SIGUSR1 수신\n");
}

int main()
{
  pid_t child_pid;

  // 자식 프로세스 생성
  child_pid = fork();

  if (child_pid == 0)
  {
    // 자식 프로세스에서 SIGUSR1 핸들러 설정
    signal(SIGUSR1, sigusr1_handler);

    printf("자식 프로세스 (PID: %d) 대기 중...\n", getpid());

    while (1)
    {
      // 무한 루프
      sleep(1);
    }
  }
  else if (child_pid > 0)
  {
    printf("부모 프로세스 (PID: %d)에서 자식 PID: %d에게 SIGUSR1 보냄\n", getpid(), child_pid);

    // SIGUSR1 시그널을 자식 프로세스에게 보냄
    kill(child_pid, SIGUSR1);

    sleep(2); // 시그널 처리를 위한 대기

    printf("부모 프로세스 종료\n");
  }

  return 0;
}
