.PHONY build: libso_stdio.so     

libso_stdio.so: source.o 
	@gcc -shared source.o -o libso_stdio.so

source.o: source.c
	@gcc -fPIC -c source.c

.PHONY clean:
	@rm *.o source
