#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
int main(int argc,char* argcv[])
{
    char arr1[80],arr2[80];
    while(1)
    {
        int fd=open("pipe1",O_RDONLY);
        read(fd,arr1,80);
        
        printf("User 1:%s\n",arr1);
        close(fd);
        fd=open("pipe1",O_WRONLY);
        fgets(arr2,80,stdin);
        write(fd,arr2,strlen(arr2)+1);
        close(fd);
    }
}