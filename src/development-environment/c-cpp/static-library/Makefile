# FileName:   Makefile
# Author:     Fasion Chan
# @contact:   fasionchan@gmail.com
# @version:   $Id$
#
# Description:
#
# Changelog:
#

.DEFAULT_GOAL := run

say.o: say.c
	gcc -o say.o -c say.c

libsay.a: say.o
	ar -crv libsay.a say.o

hello_world.o: hello_world.c
	gcc -o hello_world.o -c hello_world.c

hello_world: hello_world.o libsay.a
	gcc -o hello_world hello_world.o libsay.a

run: hello_world
	./hello_world

clean:
	rm -f *.o
	rm -f libsay.a
	rm -f hello_world
