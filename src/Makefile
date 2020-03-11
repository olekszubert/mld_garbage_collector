mld : app.o mld.o
	cc -o mld app.o mld.o

app.o : app.c 
	cc -c app.c
mld.o : mld.c mld.h
	cc -c mld.c
clean :
	rm mld app.o mld.o
