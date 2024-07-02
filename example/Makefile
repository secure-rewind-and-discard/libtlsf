CC = gcc
PURECAPFLAGS =
CFLAGS = -fstack-protector-strong -g -Wall

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


all:  tlsf_example 

# TLSF example 
tlsf_example.o: tlsf_example.c 
	$(CC) $(CFLAGS) $(PURECAPFLAGS) -c tlsf_example.c -o tlsf_example.o 

tlsf_example: tlsf_example.o  
	$(CC) $(CFLAGS) $(PURECAPFLAGS) tlsf_example.o -L../src -ltlsf -o tlsf_example  

clean:
	rm -f  *.o *.a *.core