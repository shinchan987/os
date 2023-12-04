#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
// execl
// execlp
// execv
// execvp
int main()
{
    int pid;
    pid=fork();
    if(pid==0)
    {
        // execlp("ls","ls","-l",NULL);
        char * arg[]={"ls","-l",NULL};
        execvp(arg[0],arg);

    }
    else
    {
        wait(NULL);
        printf("this is parent process\n");

    }
    return 0;
}