#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

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
    // 자식 프로세스에서 메시지 출력
    printf("자식 프로세스 시작 (PID: %d, 부모 PID: %d)\n", getpid(), getppid());
  }
  else
  {
    // 부모 프로세스에서 메시지 출력
    printf("부모 프로세스에서 자식 PID 대기 중...\n");

    // 자식 프로세스의 종료를 대기
    wait(NULL);

    printf("부모 프로세스 종료\n");
  }

  return 0;
}

// 위 프로그램은 fork 함수를 사용하여 자식 프로세스를 생성하고,
// 부모 및 자식 프로세스가 각각 메시지를 출력합니다.
//  getpid() 함수는 현재 프로세스의 PID(프로세스 ID)를 얻는 데 사용되며,
// getppid() 함수는 부모 프로세스의 PID를 얻습니다. wait(NULL) 함수는 자식 프로세스의 종료를 대기합니다.