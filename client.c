#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
void error(char *err)
{
    perror(err);
    exit(1);
}
int main(int argc,char *argv[])
{
    int sock,n;
    struct sockaddr_in serveradd;
    if(argc<3)
    {
        error("missing port number or IP address\n");
    }
    if((sock=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        error("socket creation failed to do so\n");
    }
    memset((char *)&serveradd,0,sizeof(serveradd));
    serveradd.sin_family=AF_INET;
    serveradd.sin_addr.s_addr=inet_addr(argv[1]);
    serveradd.sin_port=htons(atoi(argv[2]));
    printf("conecting to server...\n");
    if((connect(sock,(struct sockaddr *)&serveradd,sizeof(serveradd)))<0)
    {
        error("connection failed\n");
    }
    printf("server connected, start chatting\n");
    char buffer[]={"hello"};
    send(sock,buffer,sizeof(buffer),0);
}