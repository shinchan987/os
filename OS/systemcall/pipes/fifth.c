#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include<sys/wait.h>
#include<sys/types.h>

int main()
{
    system("ls -l|sort");
    return 0;
}