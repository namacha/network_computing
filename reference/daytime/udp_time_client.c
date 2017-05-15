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
#include "error_handler.h"

#define BUFF_SIZE 64   // バッファのサイズ

/*
 * UDP Daytimeクライアント
 */
int main(int argc, char *argv[]) {
  // パラメータ
  char *serv_ip = "127.0.0.1";    // ループバックアドレス
  in_port_t port_num = 5000;      // ポート番号
  struct sockaddr_in serv_addr;  // アドレス
  int n = 0;                      // 戻り値の保存用
  
  char buff[BUFF_SIZE];       // 受信用バッファ
  char query[8] = "query";    // クエリ文字列
  
  // パラメータの初期化
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(serv_ip);
  serv_addr.sin_port = htons(port_num);
  
  // ソケット作成、UDPを用いるため、第２引数にダイアグラム、第３引数にUDPを指定する。
  int socketd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (socketd < 0) handle_error("Fail to create a client socket.\n");
  
  // クエリ送信。（'query'という文字列）を送信するだけ。
  n = sendto(socketd, query, sizeof(query), 0,  (struct sockaddr*) &serv_addr, sizeof(serv_addr));
  if (n < 0) handle_error("Fail to receive a message.\n");
  
  // サーバから現在時刻を文字列として受信。
  n = recvfrom(socketd, buff, BUFF_SIZE, 0, NULL, NULL);
  if (n < 0) handle_error("Fail to receive a message.\n");
  fprintf(stderr, "Time: %s", buff);
  
  // ソケットを閉じる
  close(socketd);
}
