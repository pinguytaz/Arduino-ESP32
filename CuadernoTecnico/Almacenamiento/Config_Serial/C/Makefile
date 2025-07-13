CC_LINUX = gcc
CC_WIN = x86_64-w64-mingw32-gcc

SRC = Conf_LW.c

all: linux windows

linux: $(SRC)
	$(CC_LINUX) -o Conf_Lin.elf $(SRC)

windows: $(SRC)
	$(CC_WIN) -o Conf_Win.exe $(SRC)

clean:
	rm -f Conf_Lin.elf Conf_Win.exe

