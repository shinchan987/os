#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main()
{
    int pid;
    pid=fork();
    if(pid==0)
    {
        char * arg[]={"./a.out",NULL};
        execv(arg[0],arg);
        exit(0);

    }
    else
    {
        wait(NULL);
        printf("this is parent process\n");

    }
    return 0;
}