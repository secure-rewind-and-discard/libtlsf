CFLAGS = -fstack-protector-strong -O2
DEPS = tlsf.h
OUT_FILE_NAME = libtlsf.a

CC = gcc
PURECAPFLAGS =
CHERI = 0

ifeq ($(CHERI),1)
CC = clang
PURECAPFLAGS = -target aarch64-unknown-freebsd -march=morello -mabi=purecap -Xclang -morello-vararg=new
CFLAGS = -g -Wall -O2 -DCHERI
endif

# debug
ifeq ($(CHERI_DEBUG),1)
CC = clang
PURECAPFLAGS = -target aarch64-unknown-freebsd -march=morello -mabi=purecap -Xclang -morello-vararg=new
PURECAPFLAGS += -Wcheri-capability-misuse -Wcheri-implicit-conversion -Wshorten-cap-to-int -Wcheri-provenance
CFLAGS = -g -Wall -O2 -DCHERI
endif


all: tlsf.o  libtlsf_init.o libtlsf.a libtlsf.so

tlsf.o: tlsf.c $(DEPS)
	$(CC) -fPIC -c $(CFLAGS) $(PURECAPFLAGS) tlsf.c tlsf.h

libtlsf_init.o: libtlsf_init.c $(DEPS)
	$(CC) -fPIC -c $(CFLAGS) $(PURECAPFLAGS) libtlsf_init.c

libtlsf.a: tlsf.o libtlsf_init.o
	ar -rc libtlsf.a tlsf.o  libtlsf_init.o

libtlsf.so: tlsf.o libtlsf_init.o
	$(CC) -shared -fPIC -pthread $(CFLAGS) $(PURECAPFLAGS) -o libtlsf.so tlsf.o libtlsf_init.o

clean:
	rm -f *.o *.a *.gch *.core