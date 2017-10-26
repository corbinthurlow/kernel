#####################################################################
# ECEn 425 Lab 4b Makefile

all:
		cpp myinth.c myinth.i
		c86 -g myinth.i myinth.s
		cpp yakc.c yakc.i
		c86 -g yakc.i yakc.s
		cpp lab4b_app.c lab4b_app.i
		c86 -g lab4b_app.i lab4b_app.s
		cat clib.s yaks.s myisr.s myinth.s yakc.s lab4b_app.s > lab4bfinal.s
		nasm lab4bfinal.s -o lab4b.bin -l lab4b.lst

lab4b.bin:	lab4bfinal.s
		nasm lab4bfinal.s -o lab4b.bin -l lab4b.lst

lab4bfinal.s:	clib.s myisr.s myinth.s yakc.s lab4b_app.s
		cat clib.s yaks.s myisr.s myinth.s yakc.s lab4b_app.s > lab4bfinal.s

myinth.s:	myinth.c
		cpp myinth.c myinth.i
		c86 -g myinth.i myinth.s

yakc.s:	yakc.c
		cpp yakc.c yakc.i
		c86 -g yakc.i yakc.s

lab4b_app.s: lab4b_app.c
		cpp lab4b_app.c lab4b_app.i
		c86 -g lab4b_app.i lab4b_app.s

clean:
		rm lab4b.bin lab4b.lst lab4bfinal.s myinth.s myinth.i \
		yakc.s yakc.i lab4b_app.s lab4b_app.i
