all:  tlsf_example 

# TLSF example 
tlsf_example.o: tlsf_example.c 
	gcc -fstack-protector-strong -Wall -c tlsf_example.c   -g -o tlsf_example.o 

tlsf_example: tlsf_example.o  
	gcc -fstack-protector-strong -Wall tlsf_example.o  -L../src -ltlsf -g -o tlsf_example  

clean:
	rm -f  *.o *.a 