m_m_win32:
	sudo /usr/bin/i586-mingw32msvc-g++ -g -c glitch.cpp -o glitch_w32.o
	sudo /usr/bin/i586-mingw32msvc-g++ -g -c main.cpp -o main_w32.o
	sudo /usr/bin/i586-mingw32msvc-g++ -g -o ../bin/mediaglitch_win32.exe main_w32.o glitch_w32.o
m_m_unix:
	g++ -g -c glitch.cpp -o glitch_unix.o
	g++ -g -c main.cpp -o main_unix.o
	g++ -g -o ../bin/mediaglitch_unix main_unix.o glitch_unix.o -lncurses
all:
	m_m_win32
	m_m_unix
clean:
	rm -f -r glitch_w32.o
	rm -f -r glitch_unix.o
	rm -f -r main_w32.o
	rm -f -r main_unix.o
	rm -f -r mediaglitch_unix
	rm -f -r mediaglitch_win32.exe
