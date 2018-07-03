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
	gcc -fPIC -o say.o -c say.c

libsay.so: say.o
	gcc -shared -o libsay.so say.o

hello_world.o: hello_world.c
	gcc -o hello_world.o -c hello_world.c

hello_world: hello_world.o libsay.so
	gcc -o hello_world hello_world.o -L. -lsay

run: hello_world
	LD_LIBRARY_PATH=. ./hello_world

clean:
	rm -f *.o
	rm -f libsay.so
	rm -f hello_world
