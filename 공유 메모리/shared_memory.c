#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <semaphore.h>

int main()
{
  const char *sourceFileName = "source.txt";
  const char *targetFileName = "target.txt";
  const char *memName = "shared_memory";
  const int SIZE = 4096;

  // 세마포어 생성 및 초기화
  sem_t *sem = sem_open("/semaphore", O_CREAT, 0644, 1);
  if (sem == SEM_FAILED)
  {
    perror("sem_open");
    return EXIT_FAILURE;
  }

  // 공유 메모리 생성 및 매핑
  int fd = shm_open(memName, O_CREAT | O_RDWR, 0666);
  ftruncate(fd, SIZE);
  char *shared_memory = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  if (shared_memory == MAP_FAILED)
  {
    perror("mmap");
    return EXIT_FAILURE;
  }

  pid_t pid = fork(); // 프로세스 분기

  if (pid < 0)
  {
    // Fork 실패
    perror("fork");
    return EXIT_FAILURE;
  }
  else if (pid > 0)
  {
    // 부모 프로세스: 파일 읽기
    sem_wait(sem); // 세마포어 잠금

    FILE *sourceFile = fopen(sourceFileName, "r");
    if (sourceFile == NULL)
    {
      perror("fopen");
      sem_post(sem); // 세마포어 해제
      return EXIT_FAILURE;
    }

    fread(shared_memory, sizeof(char), SIZE, sourceFile);
    fclose(sourceFile);

    sem_post(sem); // 세마포어 해제
    wait(NULL);    // 자식 프로세스 기다림
  }
  else
  {
    // 자식 프로세스: 파일 쓰기
    sem_wait(sem); // 세마포어 잠금

    FILE *targetFile = fopen(targetFileName, "w");
    if (targetFile == NULL)
    {
      perror("fopen");
      sem_post(sem); // 세마포어 해제
      return EXIT_FAILURE;
    }

    fwrite(shared_memory, sizeof(char), SIZE, targetFile);
    fclose(targetFile);

    sem_post(sem); // 세마포어 해제
  }

  // 자원 정리
  munmap(shared_memory, SIZE);
  close(fd);
  shm_unlink(memName);
  sem_close(sem);
  sem_unlink("/semaphore");

  return EXIT_SUCCESS;
}
