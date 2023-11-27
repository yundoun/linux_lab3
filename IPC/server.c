#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
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
  int sockfd, newsockfd;
  socklen_t clilen;
  char buffer[MAX_MESSAGE_SIZE];
  struct sockaddr_in serv_addr, cli_addr;

  // 소켓 생성
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    error("소켓 생성 실패");

  // 서버 주소 설정
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(PORT);

  // 소켓 바인딩
  if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    error("바인딩 실패");

  // 클라이언트 대기
  listen(sockfd, 5);
  printf("클라이언트 연결 대기 중...\n");
  clilen = sizeof(cli_addr);

  // 클라이언트 연결 수락
  newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
  if (newsockfd < 0)
    error("클라이언트 연결 수락 실패");
  printf("클라이언트가 연결되었습니다.\n");

  while (1)
  {
    memset(buffer, 0, sizeof(buffer));
    // 클라이언트로부터 메시지 읽기
    if (read(newsockfd, buffer, sizeof(buffer)) < 0)
      error("메시지 읽기 실패");
    printf("상대방: %s\n", buffer);

    // 메시지 입력
    printf("나: ");
    memset(buffer, 0, sizeof(buffer));
    fgets(buffer, sizeof(buffer), stdin);

    // 메시지 전송
    if (write(newsockfd, buffer, strlen(buffer)) < 0)
      error("메시지 전송 실패");
  }

  close(newsockfd);
  close(sockfd);
  return 0;
}
