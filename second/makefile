all:main.o func.o
	g++ -o main1 main.o func.o
main.o:main.c
	g++ -c main.c
func.o:func.h func.c
	g++ -c func.c
clean:
	rm -rf *.o
