#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
  char input[1000];
  char sentence[1000];
  int mistakes = 0;
  clock_t start_time, end_time;
  double elapsed_time, typing_speed;

  printf("타자 연습을 시작합니다. 아래 문장을 빠르게 타이핑해보세요.\n");
  printf("문장: The quick brown fox jumps over the lazy dog.\n");

  strcpy(sentence, "The quick brown fox jumps over the lazy dog.");
  printf("입력: ");
  fgets(input, sizeof(input), stdin);

  // 개행 문자 제거
  input[strcspn(input, "\n")] = '\0';

  // 비교하여 잘못 타이핑한 횟수 계산
  for (int i = 0; i < strlen(sentence); i++)
  {
    if (sentence[i] != input[i])
    {
      mistakes++;
    }
  }

  // 시작 시간 기록
  start_time = clock();

  // 사용자가 입력을 완료할 때까지 대기 (예: Enter 키를 누를 때까지)
  printf("엔터 키를 누르면 종료됩니다.\n");
  getchar();

  // 종료 시간 기록
  end_time = clock();

  // 경과 시간 계산
  elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC * 100000;
  
  // 분당 타자수 계산
  typing_speed = ((strlen(sentence) - mistakes) / elapsed_time) * 60;

  printf("경과시간 : %.2lf(초) \n", elapsed_time);
  printf("잘못 타이핑한 횟수: %d\n", mistakes);
  printf("평균 분당 타자수: %.2f\n", typing_speed);

  return 0;
}