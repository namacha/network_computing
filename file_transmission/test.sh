#!/usr/local/bin/zsh

file="/Users/`whoami`/Desktop/test.png"

./server > /dev/null &

pid=$!

expect -c "
spawn ./client
expect \">\"
send \"test.png\n\"
expect File
exit 0
"

killall server
