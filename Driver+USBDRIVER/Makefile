obj-m += Driver2.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

all: AplicacaoUsuario
AplicacaoUsuario: AplicacaoUsuario.o
AplicacaoUsuario.o: AplicacaoUsuario.c

clean:
	rm -f AplicacaoUsuario AplicacaoUsuario.o
run: AplicacaoUsuario
	./AplicacaoUsuario
