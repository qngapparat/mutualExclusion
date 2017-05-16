
all:
	gcc creator.c -o creator.out
	gcc modifier.c -o modifier.out

clean:
	rm creator.out
	rm modifier.out

peeps:
	gcc peep1.c -o peep1.out
	gcc peep2.c -o peep2.out
