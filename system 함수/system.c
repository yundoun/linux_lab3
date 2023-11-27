#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int my_system(const char *command)
{
  pid_t pid;
  int status;

  // fork를 사용하여 자식 프로세스 생성
  pid = fork();

  if (pid < 0)
  {
    perror("fork 실패");
    return -1;
  }
  else if (pid == 0)
  {
    // 자식 프로세스에서 명령 실행
    execl("/bin/sh", "sh", "-c", command, (char *)0);

    // execl 함수가 실패하면 아래 코드가 실행됨
    perror("execl 실패");
    exit(1);
  }
  else
  {
    // 부모 프로세스에서 자식 프로세스의 종료를 대기
    wait(&status);

    // 자식 프로세스의 종료 상태 확인
    if (WIFEXITED(status))
    {
      return WEXITSTATUS(status);
    }
    else
    {
      return -1;
    }
  }
}

int main()
{
  int result;

  // 명령 실행
  result = my_system("ls -la");

  if (result == 0)
  {
    printf("명령 실행 성공\n");
  }
  else
  {
    printf("명령 실행 실패\n");
  }

  return 0;
}
