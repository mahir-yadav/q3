#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/pid.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("mahir");
MODULE_DESCRIPTION("OS assignment 3");
MODULE_VERSION("1.0");


static int pid = 1;
module_param(pid, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(pid, "The PID of the process to print information about");

static int __init process_info_init(void)
{
    struct task_struct *task;
    struct pid *pid_struct;

    printk(KERN_INFO "Process Info Module Loaded\n");

    pid_struct = find_get_pid(pid);
    task = pid_task(pid_struct, PIDTYPE_PID);

    if (!task)
    {
        printk(KERN_INFO "Unable to find task with PID %d\n", pid);
        return -ENODEV;
    }

    printk(KERN_INFO "Process Information:\n");
    printk(KERN_INFO "PID: %d\n", task->pid);
    printk(KERN_INFO "Name: %s\n", task->comm);
    printk(KERN_INFO "Priority: %d\n", task->prio);
    printk(KERN_INFO "Static Priority: %d\n", task->static_prio);

    return 0;
}

static void __exit process_info_exit(void)
{
    printk(KERN_INFO "Process Info Module Unloaded\n");
}

module_init(process_info_init);
module_exit(process_info_exit);