CFLAGS = -I ./include
##LIB    = ./libggfonts.so
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr

all: clean mazewars

mazewars: mazewars.cpp ppm.c log.c
	g++ $(CFLAGS) matthewG.cpp davidV.cpp roseP.cpp mazewars.cpp log.c /usr/lib/x86_64-linux-gnu/libopenal.so /usr/lib/libalut.so joystick.cc libggfonts.a -Wall -std=c++11 -Wextra $(LFLAGS) -o MazeWars

clean:
	rm -f MazeWars
	rm -f x.x


