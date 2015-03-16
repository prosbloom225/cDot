CC=clang
CFLAGS=-I. -Wall  -std=c99 -D_BSD_SOURCE
DEPS = 
OBJ = main.o  
LDFLAGS = -lsqlite3

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cdot: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf *.o cdot home/a home/b
	sqlite3 home/db.db "DELETE FROM dotfiles"
install:
	cp cdot /usr/bin
