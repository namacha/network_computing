#!/bin/bash

# 情報通信応用実験 ネットワークプログラミング
#
# 首都大学東京 システムデザイン学部 情報通信システムコース
# 助教・酒井 和哉
# ２０１５年４月９日

# ターゲットのアドレス、Pingの回数
target="127.0.0.1"
num_ping=1

# For-loopを用いて、各パケットサイズでpingを打つ
for size in 64 128 256 512; do
	ping -c $num_ping -s $size $target
done
