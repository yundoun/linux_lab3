#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

// SIGCHLD 핸들러 함수
void sigchld_handler(int signo)
{
  int status;
  pid_t child_pid = wait(&status);
  printf("자식 프로세스 (PID: %d) 종료\n", child_pid);
}

int main()
{
  pid_t child_pid;

  // SIGCHLD 시그널 핸들러 설정
  signal(SIGCHLD, sigchld_handler);

  // 자식 프로세스 생성
  child_pid = fork();

  if (child_pid == 0)
  {
    printf("자식 프로세스 (PID: %d) 실행 중...\n", getpid());
    sleep(2); // 일부러 지연
    printf("자식 프로세스 종료\n");
  }
  else if (child_pid > 0)
  {
    printf("부모 프로세스 (PID: %d)에서 자식 PID: %d 대기 중...\n", getpid(), child_pid);

    while (1)
    {
      // 무한 루프
      sleep(1);
    }
  }

  return 0;
}
