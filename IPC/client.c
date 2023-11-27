#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 12345
#define MAX_MESSAGE_SIZE 1024

void error(const char *msg)
{
  perror(msg);
  exit(1);
}

int main()
{
  int sockfd;
  char buffer[MAX_MESSAGE_SIZE];
  struct sockaddr_in serv_addr;

  // 소켓 생성
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    error("소켓 생성 실패");

  // 서버 주소 설정
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);
  if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    error("서버 주소 설정 실패");

  // 서버에 연결
  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    error("서버에 연결 실패");
  printf("서버에 연결되었습니다.\n");

  while (1)
  {
    // 메시지 입력
    printf("나: ");
    memset(buffer, 0, sizeof(buffer));
    fgets(buffer, sizeof(buffer), stdin);

    // 메시지 전송
    if (write(sockfd, buffer, strlen(buffer)) < 0)
      error("메시지 전송 실패");

    memset(buffer, 0, sizeof(buffer));
    // 서버로부터 메시지 읽기
    if (read(sockfd, buffer, sizeof(buffer)) < 0)
      error("메시지 읽기 실패");
    printf("상대방: %s\n", buffer);
  }

  close(sockfd);
  return 0;
}
