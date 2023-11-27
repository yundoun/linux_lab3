#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_MESSAGE_SIZE 1024

// 메시지 구조체 정의
struct msg_buffer
{
  long msg_type;
  char message[MAX_MESSAGE_SIZE];
};

int main()
{
  key_t key;
  int msgid;
  struct msg_buffer message_buffer;

  // 메시지 큐 생성
  key = ftok("/tmp", 'A');
  msgid = msgget(key, 0666 | IPC_CREAT);

  while (1)
  {
    // 메시지 입력
    printf("나: ");
    fgets(message_buffer.message, MAX_MESSAGE_SIZE, stdin);
    message_buffer.msg_type = 1;

    // 서버에게 메시지 전송
    msgsnd(msgid, &message_buffer, sizeof(message_buffer), 0);

    // 서버로부터 메시지 수신
    msgrcv(msgid, &message_buffer, sizeof(message_buffer), 1, 0);
    printf("서버: %s\n", message_buffer.message);
  }

  return 0;
}
