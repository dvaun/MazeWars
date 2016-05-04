CFLAGS = -I ./include -g
##LIB    = ./libggfonts.so
##required for Arch linux: /usr/lib/libopenal.so
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr

all: clean mazewars

mazewars: mazewars.cpp ppm.c log.c
	g++ $(CFLAGS) matthewG.cpp davidV.cpp ppm.c jobG.cpp roseP.cpp mazewars.cpp log.c\
			/usr/lib/x86_64-linux-gnu/libopenal.so /usr/lib/libalut.so\
			joystick.cc libggfonts.a -Wall -std=c++11 -Wextra $(LFLAGS)\
			-o MazeWars

clean:
	rm -f MazeWars
	rm -f x.x


