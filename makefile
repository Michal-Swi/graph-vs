make:
	g++ main.cpp -lraylib -lm -ldl -lpthread -lGL -lrt -lX11

run:
	g++ main.cpp -lraylib -lm -ldl -lpthread -lGL -lrt -lX11
	./a.out
