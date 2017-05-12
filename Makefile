All:
		gcc -Wall -std=c11 -g -c listio.c -o listio.o
		ar cr liblistio.a listio.o
		gcc -g main.c listio.c -o A4 -lmysqlclient -L/usr/lib/x86_64-linux-gnu/
		gcc db.c -o db.o -c
		gcc db.o -o db -lmysqlclient -L/usr/lib/x86_64-linux-gnu/
clean:
		$(RM)myprog
