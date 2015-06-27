#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h> 
#include <linux/fs.h> 
#include <linux/errno.h> 
#include <linux/types.h> 
#include <linux/proc_fs.h>
#include <linux/fcntl.h> 
#include <asm/uaccess.h>

//Macro responsavel pela licenca do driver
MODULE_LICENSE("GPL");

//Macro responsavel pelo nome do autor
MODULE_AUTHOR("Eduardo Beckhauser");


//Declaracao de funcoes
static int copen(struct inode *i,struct file *f);
static int crelease(struct inode *i,struct file *f);
static ssize_t cwrite(struct file *f,char *buf,size_t count,loff_t *f_pos);
static ssize_t cread(struct file *f,char *buf,size_t count,loff_t *f_pos);
//Fim de declaracao de funcoes

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


/*Struct de operacoes que poderao ser executadas pelo driver*/
static struct file_operations fops={

	.open = copen,
	.release = crelease,
	.read = cread,
	.write = cwrite
};



//Fim de Declaracao de variaveis
static int __init iniciar(void){
	/*Register_chrdev - registra um major number para character drivers, levando um major, um nome e uma strucs de operacoes como parametro*/
	resultado = register_chrdev(majorNumber, "Comunicacao", &fops);
	
	if(resultado < 0)
	{
	printk(KERN_INFO "Nao foi possivel obter o major number");
	return resultado;
	}
 
	/*Printk - mensagens de I/O com o kernel*/
	printk(KERN_INFO "Driver sendo inicializado com o major number = %d\n", majorNumber);

return 0;
}


/*Funcao responsavel por abrir um dispositivo como um arquivo*/
static int copen(struct inode *i,struct file *f){
printk(KERN_INFO "Driver sendo aberto");
return 0; // success
}



/*Funcao responsavel por ler de um dispositivo*/
static ssize_t cread(struct file *f,char *buf,size_t count,loff_t *f_pos){
return 0;
}


/*Funcao responsavel por escrever em um dispositivo*/
static ssize_t cwrite(struct file *f,char *buf,size_t count,loff_t *f_pos){return 0;}



/*Funcao responsavel por dar um release no dispositivo*/
static int crelease(struct inode *i,struct file *f)
{
return 0; // success
}

/*Funcao responsavel por desalocar memoria de tudo o que foi
alocano no __init, sendo chamado na retirada do modulo do kernel*/
static void __exit sair(void){

	printk(KERN_INFO "O driver foi encerrado.\n");
	/*Funcao que retira o dispositivo*/
	unregister_chrdev(majorNumber, "Comunicacao");

}

//Macro para a definicao da funcao de inicializar o driver
module_init(iniciar);
//Macro para a definicao da funcao de finalizar o driver
module_exit(sair);
