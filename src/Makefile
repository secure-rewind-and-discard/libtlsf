CFLAGS= -fstack-protector-strong 
DEPS = tlsf.h
OUT_FILE_NAME = libtlsf.a

all: tlsf.o  libtlsf_init.o libtlsf.a libtlsf.so

tlsf.o: tlsf.c $(DEPS)
	gcc -fPIC -c  -O2  $(CFLAGS)  tlsf.c tlsf.h

libtlsf_init.o: libtlsf_init.c $(DEPS)
	gcc  -fPIC  -c -O2   $(CFLAGS) -g libtlsf_init.c 

libtlsf.a: tlsf.o libtlsf_init.o
	ar -rc libtlsf.a tlsf.o  libtlsf_init.o

libtlsf.so: tlsf.o libtlsf_init.o
	gcc -shared  -fPIC  -pthread $(CFLAGS) -o libtlsf.so   tlsf.o  libtlsf_init.o

clean:
	rm -f *.o  *.a