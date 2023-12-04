// ignoring signal  man 7 signal

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<signal.h>
void handler(int sig)
{
    printf("Kirti\n");
}
int main(int argc,char* argcv[])
{
    signal(SIGINT,handler);
    while(1)
    {
        printf("Hello\n");
        sleep(5);
    }
    return 0;
}