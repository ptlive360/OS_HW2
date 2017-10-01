
#include <linux/module.h>
//#include <linux/slab.h>  //At first, lacks this 
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
MODULE_LICENSE("Dual BSD/GPL");

void DFS(struct task_struct *task)
{
	struct tast_struct *child;
	struct list_head *list;

	//printk("name: %s, pid: [%d], state: %li\n", task->comm, task->pid, task->state);
	printk("PID[%d]\n", task->pid);

	list_for_each(list, &task->children) {
        	child = list_entry(list, struct task_struct, sibling);
        	DFS(child);
    	}
}





static int hello_init(void)
{
	struct task_struct *task;
	printk(KERN_INFO "Loading Task Lister Module...\n");

	for_each_process(task)
	{
		//printk("Name: %s PID: [%d]\n", task->comm, task->pid);
		printk("PID[%d]\n", task->pid);
	}
	
	DFS(&init_task);
	return 0;
}
static void hello_exit(void)
{
	printk(KERN_INFO "Removing Task Lister Module...\n");
}

module_init(hello_init);
module_exit(hello_exit);

