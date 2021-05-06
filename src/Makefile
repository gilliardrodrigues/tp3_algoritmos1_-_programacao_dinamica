CC=g++
CFLAGS=-std=c++17 -Wall -Wextra
EXEC=./tp03
TMPOUT=tp03.testresult

$(EXEC): escala.cpp sistema.cpp main.cpp
	$(CC) $(CFLAGS) escala.cpp sistema.cpp main.cpp -o $(EXEC)
clean:
	rm tp03
tests: $(EXEC)
	@bash run_tests.sh $(EXEC) $(TMPOUT)