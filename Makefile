CFLAGS = -I ./include
##LIB    = ./libggfonts.so
##required for Arch linux: /usr/lib/libopenal.so
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr

all: clean mazewars

mazewars: mazewars.cpp ppm.c log.c
<<<<<<< HEAD
	g++ $(CFLAGS) matthewG.cpp davidV.cpp jobG.cpp roseP.cpp mazewars.cpp log.c /usr/lib/x86_64-linux-gnu/libopenal.so /usr/lib/x86_64-linux-gnu/libalut.so joystick.cc libggfonts.a -Wall -std=c++11 -Wextra $(LFLAGS) -o MazeWars
=======
	g++ $(CFLAGS) matthewG.cpp davidV.cpp roseP.cpp mazewars.cpp log.c\
			/usr/lib/x86_64-linux-gnu/libopenal.so /usr/lib/libalut.so\
			joystick.cc libggfonts.a -Wall -std=c++11 -Wextra $(LFLAGS)\
			-o MazeWars
>>>>>>> a5755ffe59ddd3ffa5be23e572011610cdac0acc

clean:
	rm -f MazeWars
	rm -f x.x


