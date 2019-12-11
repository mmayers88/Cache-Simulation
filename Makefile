OBJS = helper.o project.o
READFILE = readme.txt
VARIABLE=`cat $(READFILE)`


project : $(OBJS)
	gcc $(OBJS) -o project
helper.o : helper.c
	gcc helper.c -c
project.o : project.c
	gcc project.c -c
clean:
	rm $(OBJS) project
run : project
	./project test.txt
silent : project
	gcc -DSILENT helper.c project.c -o project
output : project
	./project test.txt > output.txt