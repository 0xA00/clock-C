CXX = gcc
SRC = clock.c


build:
	$(CXX) $(SRC) -o clock

run: build
	./clock

run_s : build
	./clock -s

run_c : build
	./clock -c red

run_bin : build
	sudo cp clock /usr/local/bin
