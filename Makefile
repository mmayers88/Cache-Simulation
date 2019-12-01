OBJS = helper.o project.o mesi.o
READFILE = readme.txt
VARIABLE=`cat $(READFILE)`

project : $(OBJS)
	gcc $(OBJS) -o project
helper.o : helper.c
	gcc helper.c -c
project.o : project.c
	gcc project.c -c
mesi.o : mesi.c
	gcc mesi.c -c
clean:
	rm $(OBJS) project
run : project
	./project text.txt