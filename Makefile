# (1)コンパイラ
CC  = gcc
# (2)コンパイルオプション
CFLAGS = -Wall -O2 -Werror -g3
# (3)実行ファイル名
TARGET  = bin/lru
# (4)コンパイル対象のソースコード
SRCS    = *.c
HEADER = *.h

# (5)オブジェクトファイル名
OBJS    = $(SRCS:.c=.o)

# (6)インクルードファイルのあるディレクトリパス
INCDIR  = 

# (7)ライブラリファイルのあるディレクトリパス
LIBDIR  = 

# (8)追加するライブラリファイル
LIBS    = 

# (9)ターゲットファイル生成
$(TARGET): $(OBJS)
	mkdir -p bin
	$(CC) -o $@ $^ $(LIBDIR) $(LIBS)

# (10)オブジェクトファイル生成
$(OBJS): $(SRCS) $(HEADER) Makefile
	$(CC) $(CFLAGS) $(INCDIR) -c $(SRCS)

# (11)"make all"で make cleanとmakeを同時に実施。
all: clean $(OBJS) $(TARGET)
# (12).oファイル、実行ファイル、.~ファイルを削除
clean:
	-rm -f $(OBJS) $(TARGET) *.~
