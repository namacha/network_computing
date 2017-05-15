#!/bin/bash

# 情報通信応用実験 ネットワークプログラミング
#
# 首都大学東京 システムデザイン学部 情報通信システムコース
# 助教・酒井 和哉
# ２０１５年４月９日

# コピー元のファイル名、コピー先ディレクトリ名、コピー先のファイル名
in_file="file1.txt"
dir_name="dir1"
out_file="file2.txt"

# ターミナルに文字列をエコー
echo "An example of shell scripts."
echo "コピー元ファイル名 : $in_file"
echo "コピー先ディレクトリ名 : $dir_name"
echo "コピー先ファイル名 : $out_file"

# 現在のワーキングディレクトリを表示
pwd

# ディレクトリを作成、ファイルをコピー、ディレクトリを移動、ディレクトリ内のファイルを表示、コピーしたファイルを表示
mkdir $dir_name
cp $in_file $dir_name/$out_file
cd $dir_name
ls -l
cat $out_file
