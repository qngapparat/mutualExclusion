
all:
	gcc creator.c -o creator.out
	gcc spambot.c -o spambot.out

clean:
	rm creator.out
	rm spambot.out

peeps:
	gcc peep1.c -o peep1.out
	gcc peep2.c -o peep2.out
