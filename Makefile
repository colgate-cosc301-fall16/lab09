CC=clang
CFLAGS=-g -Wall -pthread
LDFLAGS=-g -Wall -pthread

clinic: clinic.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean
clean:
	rm -f *.o clinic

