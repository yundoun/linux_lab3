#include <stdio.h>
#include <stdlib.h>

int main()
{
  FILE *sourceFile, *targetFile;
  char ch;

  sourceFile = fopen("source.txt", "r");
  if (sourceFile == NULL)
  {
    printf("Cannot open source file.\n");
    exit(1);
  }

  targetFile = fopen("target.txt", "w");
  if (targetFile == NULL)
  {
    printf("Cannot create target file.\n");
    fclose(sourceFile);
    exit(1);
  }

  while ((ch = fgetc(sourceFile)) != EOF)
  {
    fputc(ch, targetFile);
  }

  printf("File copied successfully.\n");

  fclose(sourceFile);
  fclose(targetFile);

  return 0;
}