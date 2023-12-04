// reading program

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
        int fd=open("pipe1",O_WRONLY);
        fgets(arr1,80,stdin);
        write(fd,arr1,strlen(arr1)+1);
        close(fd);
        fd=open("pipe1",O_RDONLY);
        read(fd,arr2,80);
        printf("User 2:%s\n",arr2);
        close(fd);
    }
}