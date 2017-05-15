/*
 * 情報通信応用実験 ネットワークプログラミング
 *
 * 首都大学東京 システムデザイン学部 情報通信システムコース
 * 助教・酒井和哉
 * ２０１５年２月５日
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

#define BUFF_SIZE 64   // バッファのサイズ

int main(int argc, char *argv[]) {
  // サーバのアドレスとポート番号
  // 127.0.0.1は、ループバックアドレス
  // 他のPCと通信する場合は、当該PCのIPアドレスに変更する。
  char *serv_ip = "127.0.0.1";
  in_port_t serv_port = 5000;
  
  // 受信用バッファ、戻り値の保存用に使う変数。
  char buff[BUFF_SIZE];
  int n = 0;
  
  // ソケット作成、入力はIP、ストリーム型、TCPを指定。
  int socketd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (socketd < 0) handle_error("Fail to create a socket.\n");
  
  // サーバのアドレス等を初期化。
  struct sockaddr_in serv_addr;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(serv_ip);
  serv_addr.sin_port = htons(serv_port);
  
  // サーバに接続する。
  n = connect(socketd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
  if (n < 0) handle_error("Fail to connect to the server.\n");
  
  // 接続すると、サーバは現在時刻を文字列として返信する。
  // read(.)により、データを受信する。
  n = read(socketd, buff, sizeof(buff));
  if (n < 0) handle_error("Fail to read from a socket.\n");
  
  // サーバからの返信された文字列（現在時刻）を表示
  fprintf(stderr, "%s", buff);
  
  // close the socket
  close(socketd);
}
