#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/uaccess.h>

SYSCALL_DEFINE1(process_info, pid_t, pid)
{
    struct task_struct *task;

    // Find the task_struct for the given pid
    for_each_process(task)
    {
        if (task->pid == pid)
            break;
    }

    // Print the values of the specified fields
    printk("pid: %d\n", task->pid);
    printk("uid: %d\n", task->uid);
    printk("pgid: %d\n", task->pgid);
    printk("comm: %s\n", task->comm);

    return 0;
}

static int __init init_syscall(void)
{
    int ret;

    // Register the system call
    ret = syscall_register(process_info, __NR_process_info);
    if (ret != 0)
    {
        printk(KERN_ERR "Failed to register system call\n");
        return ret;
    }

    return 0;
}

static void __exit exit_syscall(void)
{
    // Unregister the system call
    syscall_unregister(__NR_process_info);
}

MODULE_LICENSE("GPL");
module_init(init_syscall);
module_exit(exit_syscall);
