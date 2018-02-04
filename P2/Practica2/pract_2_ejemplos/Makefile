CFLAGS = -Wall -g
clean:
	rm -rf build
	
all:
	@mkdir -p build/
	g++ $(CFLAGS) -o build/ejemplo_1 ejemplo_1.cpp
	g++ $(CFLAGS) -o build/ejemplo_2 ejemplo_2.cpp
	g++ $(CFLAGS) -o build/ejemplo_3 ejemplo_3.cpp
	g++ $(CFLAGS) -o build/ejemplo_4 ejemplo_4.cpp

ejemplo_4: ejemplo_4.cpp
	@mkdir -p build/
	g++ $(CFLAGS) -o build/ejemplo_4 ejemplo_4.cpp	