#include <stdio.h>
#include <fcntl.h>
#include "ioctl_basic.h"
main () {
        int i,fd;
        char ch, bufferEscrita[100], bufferLeitura[100];

        fd = open("/dev/EposMote", O_RDWR);

        if (fd == -1)
        {
                printf("Erro na abertura do arquivo\n");
                exit(-1);
        }
        printf ("Pressione r para ler do dispositivo ou w para escrever no dispositivo");
        scanf ("%c", &ch);


        switch (ch) {
                case 'w':
                       printf ("Entre com os dados para serem escritos no dispositivos: ");
                        scanf (" %[^\n]", bufferEscrita);
                        write(fd, bufferEscrita, sizeof(bufferEscrita));
                        break;
                case 'r':

                        read(fd, bufferLeitura, sizeof(bufferLeitura));
                        printf ("Os dados do dispositivo sao:  %s\n", bufferLeitura);
                        break;
		case 'i':	
			ioctl(fd,IOCTL_HELLO);
			break;

                default:
                        printf("Comando indefinido. \n");
                        break;
        }
        close(fd);
}

