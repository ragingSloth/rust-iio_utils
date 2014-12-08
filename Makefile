c_iio:
	gcc -Wall -fPIC -c *.c -o libiio.o -liio_utils.h
	gcc -shared -Wl,-soname,libiio.so -o libiio.so libiio.o
	rm libiio.o
