#include <linux/module.h>
#include <linux/usb.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/uaccess.h> 
#include <linux/semaphore.h>
#include <linux/cdev.h>
#include <linux/version.h> 
#include <linux/serial.h>
#include "ioctl_basic.h"
#define USB_VENDOR_ID	0x0403
#define USB_PRODUCT_ID	0x6001

//declaracoes
static int Major;
/*Data type que representa um par major/minor number*/
dev_t dev_no,dev;
long ioctl_funcs(struct file *filp,unsigned int cmd, unsigned long arg);
struct file_operations fops;
static struct usb_class_driver class;

static int usbprobe(struct usb_interface *interface, const struct usb_device_id *id){
	printk(KERN_INFO "USB esta plugado!");	
	usb_register_dev(interface, &class); 
	return 0;
}

//Chamada quando o dispositivo eh desconectado 
static void disconnect(struct usb_interface *interface){
	printk(KERN_INFO "USB foi desplugado!");
	usb_deregister_dev(interface, &class);	
}

static struct usb_device_id table[]={
	//idVendor 03eb:0902 idProduct EPOS -> 0403:6001
	{USB_DEVICE(USB_VENDOR_ID,USB_PRODUCT_ID)}, 
	{} //suportando somente um device
};
//necessario para avisar as ferramentas do user-space quais dispositivos esse driver pode controlar.
MODULE_DEVICE_TABLE(usb, table);


static struct usb_driver driver ={
	.name = "Driver de Comunicacao entre dois PCs", //nomeando o driver
	.id_table = table, //Combinar esse driver com qualquer dispositivo conectado ao USB //usb_device_id
	.probe = usbprobe, //Chamado quando um device eh plugado no computador
	.disconnect = disconnect
};

static struct usb_class_driver class ={
	.name = "EposMote", 
	.fops = &fops,
};

/*
Struct que cria um novo dispositivo com um array associado. Esse array guarda uma mensagem enviada pelo usuario.
O semaforo sem eh utilizado para tratar acesso concorrente ao dispositivo
*/
struct dev {
 char array[100];
 struct semaphore sem;
}char_arr;

/*
Funcao que abre um novo dispositivo
inode
filp  - ponteiro para arquivo que sera aberto

Somente um processo pode abrir o semaforo por vez
*/
int open(struct inode *inode, struct file *filp)
{
 printk(KERN_INFO "Abrindo dispositivo\n");

 if(down_interruptible(&char_arr.sem)) {
  printk(KERN_INFO "Problemas com o semaforo");
  return -1;
 }
 return 0;
}


/*
Funcao que le o que esta gravado no array do dispositivo.
filp - 
buff - buffer ao qual serao gravados os dados do dispositivo
count-
offp - ponteiro para o offset sendo lido do arquivo
*/
ssize_t read(struct file *filp, char *buff, size_t count, loff_t *offp) {
 unsigned long ret;
 printk("Tentando ler...\n");
 ret = copy_to_user(buff, char_arr.array, count);
 return ret;
}

/*
Funcao que escreve o que foi escrito na aplicacao do usuario e passa para o array do device
*/
ssize_t write(struct file *filp, const char *buff, size_t count, loff_t *offp) { 
 unsigned long ret;
 printk(KERN_INFO "Tentando escrever...\n");
 ret = copy_from_user(char_arr.array, buff, count);
 return count;
}

/*
Funcao que libera o driver
*/
int release(struct inode *inode, struct file *filp) {
 printk(KERN_INFO "Liberando semaforo");
 up(&char_arr.sem);
 return 0;
}

/*
Set de function pointers que o driver pode escolher para implementar 
as funcoes das quais necessita. Aqui sao informadas quais funcoes 
o kernel deve chamar para cada operacao.
*/
struct file_operations fops = {
 read:  read, //lado esquerdo significa a funcao que queremos dar suporte o lado direito, aquela que implementara essa funcao
 write:  write,
 open:   open,
 release: release,
//usados pelo ioctl para comunicacao
 unlocked_ioctl: ioctl_funcs
};

//funcao do ioctl
long ioctl_funcs(struct file *filp,unsigned int cmd, unsigned long arg){
int ret=0;
switch(cmd) {
case IOCTL_HELLO: 
 printk(KERN_INFO "Ola mundo - ioctl");
 break;
 } 
return ret;
}

/*Struct utilizada para termos conhecimento dos char devs*/
struct cdev *kernel_cdev;


/*
Funcao chamada no momento que inserimos o modulo no kernel.
*/
int iniciar(void) {
 int ret;
 ret = usb_register(&driver);
if(ret == -1)
printk(KERN_INFO "Erro ao registrar o usb");
 //inicializa o kernel_cdev
 kernel_cdev = cdev_alloc();
//Aloca o fops na estrutura do cdev 
 kernel_cdev->ops = &fops;
 kernel_cdev->owner = THIS_MODULE;
 printk ("Tentando inicializar o Driver.\n");

//Aloca um major number dinamicamente para o nodo
//recebe um data type, um firstMinor, onde temos somente um, 
//um count de major numbers que serao alocados e um nome para os 
//major numbers alocados
  ret = alloc_chrdev_region(&dev_no , 0, 1,"dispositivo");
//Verifica se o alloca_chrdev_region falhou em alocar um major number
if (ret < 0) {
  printk("Nao foi possivel alocar um novo Major Number\n");
  return ret; 
 }
//Aloca um major number a partir da macro MAJOR em dev_no
 Major = MAJOR(dev_no);
//Com a macro MKDEV, o mesmo recebe dois numeros e aloca em dev, outro data type
 dev = MKDEV(Major,0);

 sema_init(&char_arr.sem,1); 
 printk ("O major number alocado para esse dispositivo eh: %d\n", Major);

 //Adiciona a estrutura no kernel
 ret = cdev_add(kernel_cdev,dev,1);
 if(ret < 0)
 {
 printk(KERN_INFO "Impossivel alocar um cdev");
 return ret;
 }
 return 0;
}

/*
Funcao chamada quando o driver eh retirado do kernel
*/
void cleanup(void) {
 //deleta a estrutura alocada no kernel
 cdev_del(kernel_cdev);
 usb_deregister(&driver);
 printk(KERN_INFO "O modulo foi retirado do kernel\n");
}

MODULE_LICENSE("GPL"); 

//define as funcoes de init e exit
module_init(iniciar);
module_exit(cleanup);
