CC = g++
CFLAGS = -std=c++11

all: test.o sha256.o uint256.o utilstrencodings.o
	$(CC) $(CFLAGS) test.o sha256.o uint256.o utilstrencodings.o -o test 

test.o: test.cpp
	$(CC) $(CFLAGS) -c test.cpp

sha256.o: sha256.cpp sha256.h
	$(CC) $(CFLAGS) -c sha256.cpp

uint256.o: uint256.cpp uint256.h
	$(CC) $(CFLAGS) -c uint256.cpp


utilstrencodings.o: utilstrencodings.cpp utilstrencodings.h tinyformat.h
	$(CC) $(CFLAGS) -c utilstrencodings.cpp

clean:
	rm *.o test
