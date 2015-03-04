CC=gcc
CFLAGS=-I. -Wall  -std=c99 -D_BSD_SOURCE
DEPS = 
OBJ = main.o  
LDFLAGS = 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cdot: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf *.o cdot home/*
