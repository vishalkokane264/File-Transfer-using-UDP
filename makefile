target:HostA.o HostB.o HostC.o
	gcc -o getinfo HostA.o HostB.o HostC.o
HostA.o:HostA.c 
	gcc -c HostA.c 
HostB.o:HostB.c 
	gcc -c HostB.c 
HostC.o:HostC.c 
	gcc -c HostC.c 
