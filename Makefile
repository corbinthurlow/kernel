#####################################################################
# ECEn 425 Lab 4b Makefile

all:
		cpp myinth.c myinth.i
		c86 -g myinth.i myinth.s
		cpp yakc.c yakc.i
		c86 -g yakc.i yakc.s
		cpp lab_app.c lab_app.i
		c86 -g lab_app.i lab_app.s
		cat clib.s yaks.s myisr.s myinth.s yakc.s lab_app.s > labfinal.s
		nasm labfinal.s -o lab.bin -l lab.lst

lab.bin:	labfinal.s
		nasm labfinal.s -o lab.bin -l lab.lst

labfinal.s:	clib.s myisr.s myinth.s yakc.s lab4b_app.s
		cat clib.s yaks.s myisr.s myinth.s yakc.s lab_app.s > labfinal.s

myinth.s:	myinth.c
		cpp myinth.c myinth.i
		c86 -g myinth.i myinth.s

yakc.s:	yakc.c
		cpp yakc.c yakc.i
		c86 -g yakc.i yakc.s

lab_app.s: lab_app.c
		cpp lab_app.c lab_app.i
		c86 -g lab_app.i lab_app.s

clean:
		rm lab.bin lab.lst labfinal.s myinth.s myinth.i \
		yakc.s yakc.i lab_app.s lab_app.i
