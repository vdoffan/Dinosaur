all:
	g++ -c main.cpp
	g++ main.o -o game -lsfml-graphics -lsfml-window -lsfml-system
	./game
clean:
	rm *.o game 2>/dev/null || true