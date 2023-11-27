#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
  pid_t child_pid;

  // 부모 프로세스에서 메시지 출력
  printf("부모 프로세스 시작 (PID: %d)\n", getpid());

  // 자식 프로세스 생성
  child_pid = fork();

  if (child_pid < 0)
  {
    // 오류 처리
    perror("fork 실패");
    return 1;
  }
  else if (child_pid == 0)
  {
    // 자식 프로세스에서 다른 프로그램 실행
    printf("자식 프로세스에서 다른 프로그램 실행\n");
    execlp("ls", "ls", NULL); // ls 명령 실행

    // execlp 함수는 실행에 실패하면 아래 코드가 실행됨
    perror("execlp 실패");
    exit(1);
  }
  else
  {
    // 부모 프로세스에서 자식 프로세스의 종료를 대기
    wait(NULL);

    printf("부모 프로세스 종료\n");
  }

  return 0;
}

// 위 프로그램은 execlp 함수를 사용하여 ls 명령을 실행합니다.
// execlp 함수는 현재 프로세스를 다른 프로그램으로 교체하므로, 자식 프로세스에서 다른 프로그램을 실행할 때 사용됩니다.
// 프로그램을 컴파일하고 실행하면 자식 프로세스가 ls 명령을 실행하고, 부모 프로세스가 대기한 후 종료됩니다.