CC = gcc

all: standard_sha256_test.o standard_sha256.o
	$(CC) standard_sha256_test.o standard_sha256.o -o test 

standard_sha256_test.o: standard_sha256_test.c standard_sha256.h
	$(CC) -c standard_sha256_test.c

standard_sha256.o: standard_sha256.c standard_sha256.h
	$(CC) -c standard_sha256.c


clean:
	rm *.o test
