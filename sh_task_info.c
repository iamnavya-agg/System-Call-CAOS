#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/file.h> 
#include <linux/fs.h>
#include <linux/fcntl.h> 
#include <linx/unistd.h> 
#include "task_info.h"

smlinkage long sys_sh_task_info(int pid, char* filename) 
{
	if (pid <= 0 || pid > 32768)
		return -EINVAL;
	struct task_struct *task;
	struct file *file;
	loff_t pos = 0;
	char data[500], concat[500];
	int fd;

  	mm_segment_t old_fs = get_fs();
  	set_fs(KERNEL_DS);

  	fd = sys_open(filename, O_WRONLY | O_CREAT, 0644);
	for_each_process(task)
	{
		if ((int)task->pid == pid)
		{
			printk("PID Number: %ld\n", (long)task->pid);
			strcpy(data, "PID NUmber: ");
			sprintf(concat, "%ld\n", (long)task->pid);
			strcat(data, concat);
            
            printk("Process: %s\n", task->comm);
			strcat(data, "Process: ");
			strcat(data, task->comm);
			strcat(data, "\n");
			
			printk("Priority: %ld\n", (long)task->prio);
			strcat(data, "Priority: ");
			sprintf(concat, "%ld\n", (long)task->prio);
			strcat(data, concat);
            
            printk("Process State: %ld\n", (long)task->state);
			strcat(data, "Process State: ");
			sprintf(concat, "%ld\n", (long)task->state);
			strcat(data, concat);
			
            if (fd < 0)
				return -EISDIR;
			file = fget(fd);
			if (file)
			{
				vfs_write(file, data, strlen(data), &pos);
				fget(file);
			}
		}
		printk("\n\n");
	}
	set_fs(old_fs);
	return 0;
}