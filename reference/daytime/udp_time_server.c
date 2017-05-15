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
#include <arpa/inet.h>
#include <string.h>
#include <time.h>
#include "error_handler.h"

#define BUFF_SIZE 64  // バッファのサイズ

/*
 * UDP Daytimeサーバ.
 *
 */
int main(int argc, char *argv[]) {
  // パラメータ
  struct protoent *protocol_entry;          // プロトコルDBからエントリーを取得
  int port_num = 5000;                      // 待ち受けポート番号
	struct sockaddr_in serv_addr, clnt_addr;  // サーバとクライアントのソケットアドレス
	int serv_socket;                          // ソケット記述子
  int addr_len;                             // アドレス長
  int n = 0;                                // 戻り値の保存用
  
  char buff[BUFF_SIZE]; // 送信用バッファ
  time_t now;           // 現在時刻の保存用変数
  
  // パラーメータ初期化
  serv_addr.sin_family = AF_INET;           // IPv4 プロトコルファミリー
  serv_addr.sin_addr.s_addr = INADDR_ANY;   // インターネットアドレス
  serv_addr.sin_port = htons(port_num);     // ポート番号設定
  
  // プロトコルエントリー取得、戻り値が−１の場合はエラー
  protocol_entry = getprotobyname("udp");
  if (protocol_entry == NULL) handle_error("Unknown protocol.\n");
  
  // ソケット作成
  // 引数にIPv4, データグラム、TCPを指定する。
  serv_socket = socket(AF_INET, SOCK_DGRAM, protocol_entry->p_proto);
  if (serv_socket < 0) handle_error("Fail to create a socket.\n");
  
  // バインド（ソケットとポートの結合）
  if (bind(serv_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    handle_error("Fail to bind a socket.\n");
    
  // クライアントからのクエリを待ち受け。
  while (1) {
    // クライアントからクエリ文字列を待ち受ける。
    // UDPはコネクションを確立しないため、クライアントがクエリ文字列を送ってくるのを待機。
    printf("waiting for a client...\n");
    addr_len = sizeof(clnt_addr);
    n = recvfrom(serv_socket, buff, 256, 0, (struct sockaddr *)&clnt_addr, &addr_len);
    if (n < 0) handle_error("Fail to read a query from the socket.\n");
    printf("Received a query from [%s, %d]\n", inet_ntoa(clnt_addr.sin_addr), clnt_addr.sin_port);
    
    // 現在時刻取得
    time(&now);
    sprintf(buff, "%s", ctime(&now));
    
    // 現在時刻を文字列として、クライアントに送信する。
    n = sendto(serv_socket, buff, BUFF_SIZE, 0, (struct sockaddr *)&clnt_addr, sizeof(clnt_addr));
    if (n < 0) handle_error("Fail to write a message to the socket.\n");
    
  }
  
  // ソケットを閉じる。
  close(serv_socket);
  return 0;
}