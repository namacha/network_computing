#!/usr/local/bin/zsh

file="/Users/`whoami`/Desktop/test.png"

./server > /dev/null &

pid=$!

expect -c "
spawn ./client
expect \">\"
send \"${file}\n\"
expect File
exit 0
"

killall server
