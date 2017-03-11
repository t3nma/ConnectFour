ConnectFour: obj/main.o obj/State.o obj/Column.o
	g++ -std=c++11 -o ConnectFour obj/main.o obj/State.o obj/Column.o -Wall

obj/main.o: src/main.cpp src/State.cpp src/Column.cpp src/headers/State.h src/headers/Column.h
	g++ -std=c++11 -o obj/main.o -c src/main.cpp -Wall

obj/State.o: src/State.cpp src/Column.cpp src/headers/State.h src/headers/Column.h
	g++ -std=c++11 -o obj/State.o -c src/State.cpp -Wall

obj/Column.o: src/Column.cpp src/headers/Column.h
	g++ -std=c++11 -o obj/Column.o -c src/Column.cpp -Wall

clean:
	rm -f ConnectFour src/*~ obj/*.o src/*\#
