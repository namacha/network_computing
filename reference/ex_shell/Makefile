# -*- coding: utf-8; tab-width:4; indent-tabs-mode:nil -*-
#
# 情報通信応用実験 ネットワークプログラミング
#
# 首都大学東京 システムデザイン学部 情報通信システムコース
# 助教・酒井 和哉
# ２０１５年４月９日

# Your name	:
# Your ID		: 
# Date		: 

CC    = gcc
FILE   = Makefile ex_shell.sh ex_ping.sh file1.txt
OBJ   = 
OBJ_U	= 
DIR    = ex_shell

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
	