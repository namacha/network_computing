# -*- coding: utf-8; tab-width:4; indent-tabs-mode:nil -*-
#
# 情報通信応用実験 ネットワークプログラミング
#
# 首都大学東京 システムデザイン学部 情報通信システムコース
# 助教・酒井 和哉
# ２０１５年２月７日

# Your name	:
# Your ID		: 
# Date		: 

CC    = gcc
FILE   = Makefile ex_segfault.c segfault_01.png segfault_02.png segfault_03.png
OBJ   = ex_segfault
OBJ_U	= 
DIR    = ex_gdb

# -g	: ファイルにデバッグ情報を追加する。
# -O0	: 最適化を行わない。デバッグしやすくなる。
all: $(OBJ_U)
	$(CC) -w -g -O0 ex_segfault.c -o ex_segfault $(OBJ_U)

.c.o:
	$(CC) -c $<

pkg:
	# directory
	if [ ! -d $(DIR) ]; then \
		mkdir $(DIR); \
	fi
	
	# copy files
	for var in $(FILE); do\
		cp $$var $(DIR)/$$var; \
	done \
	
	# tar.gz
	tar zcvf $(DIR).tar.gz $(DIR)
	rm -r $(DIR)
	
clean:
	rm $(OBJ) $(OBJ_U)
	