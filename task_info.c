#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char** argv)
{  
	printf("        Test code to test execution of 'sh_task_info' system call\n");
	int pid=atoi(argv[1]);
    char* ff = argv[2];
	long int status = syscall(318, pid, ff); 
	if(status == 0) 
		printf("System Call 'sh_task_info' executed correctly.\n");

	else 
	{
		printf("System call 'sh_task_info' execution failed\n");
		perror("Error : ");
		printf("Error No.: %d\n", errno);
	}
	return 0;
}