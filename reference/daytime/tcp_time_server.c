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

#define BUFF_SIZE 64   // バッファのサイズ

int main(int argc, char *argv[]) {
  // パラメータ
  struct protoent *protocol_entry;          // ロトコルDBからエントリーを取得
  int port_num = 5000;                      // ポート番号
  
  struct sockaddr_in serv_addr, clnt_addr;  // ソケットアドレス
  int serv_socket, clnt_socket;             // ソケット記述子
  int addr_len;                             // アドレス長
  int n;                                    // 戻り値の保存用
  
  time_t now;             // 時間
  char *buff[BUFF_SIZE];  // 送信用バッファ（６４バイト）
  
  // パラメータの初期化
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(port_num);
  addr_len = sizeof (clnt_addr);
  
  // プロトコルエントリーを取得
  // "tcp"を引数にすると、TCPに関するエントリーを取得
  protocol_entry = getprotobyname("tcp");
  if (protocol_entry == NULL) handle_error("Unknown protocol\n");
  
  // 接続要求受付用のソケットを作成。
  // ソケット記述子（Socket descripter）が戻り値であるが、エラーが起こった場合は「-1」が返される。
  serv_socket = socket(AF_INET, SOCK_STREAM, protocol_entry->p_proto);
  if (serv_socket < 0) handle_error("Fail to create socket.\n");
  
  // バインド（ソケットとポートの結合）
  if (bind(serv_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    handle_error("Fail to bind a socket.");
  
  // ソケットをコネクション受け入れ可能な状態にする。
  // 第２引数は、接続キューのサイズ。５つまで同時接続を受け入れると指定。
  if (listen(serv_socket, 5) < 0) handle_error("Fail to listen to a socket.\n");
  
  // クライアントから接続要求があれば、順次対応
  while (1) {
    // accept(.)により、クライアントからの接続要求を受け付ける。
    // 戻り値はクライアントとのデータ通信用ソケット記述子、エラーの場合は０以下の値が返される。
    fprintf(stderr, "Waiting for a client...\n");
    clnt_socket = accept(serv_socket, (struct sockaddr *) &clnt_addr, &addr_len);
    
    // クライアントのIPアドレスとポート番号を表示。
    // それぞれ、struct sockaddr_inから取得。
    // inet_ntoa(.)は、arpa/inet.hで定義されている（Unix系の場合）。
    fprintf(stderr, "Accepted a connection from [%s, %d]\n", inet_ntoa(clnt_addr.sin_addr), clnt_addr.sin_port);
    
    // time(.)で現在時間取得（秒単位の歴時間）、ctime(.)で文字列に変換し、送信バッファに書き込み。
    time(&now);
    sprintf(buff, "%s", ctime(&now));
    
    // クライアントソケットにバッファの内容を書き込む。
    n = write(clnt_socket, buff, sizeof(buff));
    buff[0] = '\0';
    
    // クライアントとの通信は終了したので、ソケットを閉じる。
    close(clnt_socket);
  }
  
  // 受付用のソケットを閉じる。
  close(serv_socket);
  return 0;
}
