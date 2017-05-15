/*
 * 情報通信応用実験 ネットワークプログラミング
 *
 * 首都大学東京 システムデザイン学部 情報通信システムコース
 * 助教・酒井和哉
 * ２０１５年１月２８日
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "error_handler.h"

void handle_error(char *msg) {
  printf("%s", msg);
  exit(1);
}
