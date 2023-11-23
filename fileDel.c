#include <stdio.h>
#include <stdlib.h>

int main()
{
  char *fileName = "file_to_delete.txt";

  if (remove(fileName) == 0)
  {
    printf("File '%s' deleted successfully.\n", fileName);
  }
  else
  {
    printf("Failed to delete file '%s'.\n", fileName);
  }

  return 0;
}


