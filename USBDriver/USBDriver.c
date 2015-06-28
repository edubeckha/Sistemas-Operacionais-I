#include <linux/module.h>
#include <linux/usb.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/uaccess.h> 
#include <linux/semaphore.h>
#include <linux/cdev.h>
#include <linux/version.h> 
#include <linux/serial.h>


//probe function
static int usbprobe(struct usb_interface *interface, const struct usb_device_id *id){
	printk(KERN_INFO "Epos esta plugado!");
	return 0;
}

//disconnect device 
static void disconnect(struct usb_interface *interface){
	printk(KERN_INFO "Epos foi desplugado!");
}

static struct usb_device_id table[]={
	//idVendor 03eb:0902 idProduct EPOS -> 0403:6001
	{USB_DEVICE(0x0403,0x6001)}, 
	{} //suportando somente um device, o hub, pois so teremos um no projeto...
};
MODULE_DEVICE_TABLE(usb, table);


static struct usb_driver driver ={
	.name = "Driver de Comunicacao entre dois PCs", //nomeando o driver
	.id_table = table, //Combinar esse driver com qualquer dispositivo conectado ao USB //usb_device_id
	.probe = usbprobe, //Chamado quando um device eh plugado no computador
	.disconnect = disconnect
};


int iniciar(void){
	int ret = -1;
	printk(KERN_INFO "Registrando o driver no kernel...");
	ret = usb_register(&driver); //registrando o hub no core USB
	if(ret == -1)
	printk(KERN_INFO "Registro esta errado");
	printk(KERN_INFO "Registro completo");
	return ret;
}


void sair(void){
	usb_deregister(&driver);
	printk(KERN_INFO "Driver sendo removido");
}

MODULE_LICENSE("GPL");
module_init(iniciar);
module_exit(sair);
