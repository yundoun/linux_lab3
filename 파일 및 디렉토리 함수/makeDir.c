#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
  char *dirName = "new_directory1";

  if (mkdir(dirName, 0755) == 0)
  {
    printf("Directory '%s' created successfully.\n", dirName);
  }
  else
  {
    printf("Failed to create directory '%s'.\n", dirName);
  }

  return 0;
}
