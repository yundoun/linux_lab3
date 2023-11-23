#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

// 재귀적으로 디렉토리 내의 파일과 디렉토리를 나열하는 함수
void listFilesAndDirectories(const char *path)
{
  // 디렉토리를 열고 그 디렉토리 내의 파일 및 디렉토리를 나열합니다.
  struct dirent *entry;
  DIR *dp = opendir(path);

  // 디렉토리를 열지 못하면 오류 메시지를 출력하고 리턴합니다.
  if (dp == NULL)
  {
    perror("opendir");
    return;
  }

  // 디렉토리 내의 각 항목을 읽어오고 출력합니다.
  while ((entry = readdir(dp)))
  {
    // 파일 또는 디렉토리의 상세 정보를 얻어옵니다.
    struct stat statbuf;
    char fullpath[1024]; // 경로를 저장할 버퍼

    // 항목의 경로를 생성합니다.
    snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

    // 항목의 상세 정보를 얻어옵니다.
    if (lstat(fullpath, &statbuf) < 0)
    {
      perror("lstat");
      continue;
    }

    // 디렉토리일 경우 디렉토리 이름과 함께 재귀 호출합니다.
    if (S_ISDIR(statbuf.st_mode))
    {
      // "."와 ".." 디렉토리를 무시합니다.
      if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
      {
        continue;
      }

      printf("디렉토리: %s/\n", fullpath);
      listFilesAndDirectories(fullpath); // 재귀 호출
    }
    else
    {
      // 파일일 경우 파일 이름을 출력합니다.
      printf("파일: %s\n", fullpath);
    }
  }

  closedir(dp);
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    fprintf(stderr, "Usage: %s <디렉토리 경로>\n", argv[0]);
    return 1;
  }

  const char *path = argv[1];
  printf("디렉토리 내용을 나열합니다: %s\n", path);
  listFilesAndDirectories(path);

  return 0;
}