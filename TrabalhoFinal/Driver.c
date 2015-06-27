#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h> 
#include <linux/fs.h> 
#include <linux/errno.h> 
#include <linux/types.h> 
#include <linux/proc_fs.h>
#include <linux/fcntl.h> 

//Macro responsavel pela licenca do driver
MODULE_LICENSE("GPL");

//Macro responsavel pelo nome do autor
MODULE_AUTHOR("Eduardo Beckhauser");




//Declaracao de variaveis
//Inteiro que verifica se o device foi registrado com sucesso
int resultado;

//Inteiro que identifica o ID do computador para aquele driver
static int idPC __initdata = 0;
module_param(idPC, int, 0);

//Ponteiro para char que servira como buffer para a troca de mensagens
char* mensagem;

//Inteiro que disponibiliza o Major Number associado aos dispositivos
unsigned int majorNumber = 45;


static struct file_operations fops={};

//Fim de Declaracao de variaveis
static int __init iniciar(void){

	/*Register_chrdev - registra um major number para character drivers, levando um major, um nome e uma strucs de operacoes como parametro*/
	resultado = register_chrdev(majorNumber, "Comunicacao", &fops);
	
	/*Printk - mensagens de I/O com o kernel*/
	printk(KERN_INFO "Driver sendo inicializado");

return 0;
}

static void __exit sair(void){

	printk(KERN_INFO "O driver foi encerrado.\n");
	/*Funcao que retira o dispositivo*/
	unregister_chrdev(majorNumber, "Comunicacao");

}









//Macro para a definicao da funcao de inicializar o driver
module_init(iniciar);
//Macro para a definicao da funcao de finalizar o driver
module_exit(sair);