#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h> /* printk() */
#include <linux/slab.h> /* kmalloc() */
#include <linux/fs.h> /* everything... */
#include <linux/errno.h> /* error codes */
#include <linux/types.h> /* size_t */
#include <linux/proc_fs.h>
#include <linux/fcntl.h> 

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Eduardo Beckhauser");
int result;

static int idComputador __initdata = 0;
module_param(idComputador, int, 0);

void cread(struct file *filp, char *buf, size_t count, loff_t *f_pos);
void cwrite(struct file *filp, char *buf, size_t count, loff_t *f_pos);
int copen(struct inode *inode, struct file *filp);
int crelease(struct inode *inode, struct file *filp);

struct file_operations operations = {
  read: cread,
  write: cwrite
  open: copen,
  release: crelease
};

void cread(struct file *filp, char *buf, size_t count, loff_t *f_pos){}
void cwrite(struct file *filp, char *buf, size_t count, loff_t *f_pos){}


static int __init message_init(void)
{
	result = register_chrdev(bufferMensagem, "comunicacao", 0);
	printk(KERN_INFO "Driver sendo executado no computador %d\n", idComputador);
	return 0;
}

static void __exit message_exit(void)
{
	printk(KERN_INFO "O driver foi finalizado.\n");
	unregister_chrdev(bufferMensagem,"comunicacao");
}

/*Macros para definicao das funcoes de init e exit*/
module_init(message_init);
module_exit(message_exit);

/*Major number*/
int comunicacao_major = 45;
/*BUffer para trocar mensagens*/
char* bufferMensagem;

