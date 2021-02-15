#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
void error(char *err)
{
    perror(err);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sock,othersock;
    struct sockaddr_in serveradd,clientadd;
    socklen_t client;
    if(argc<2)
    {
        error("somthing is missing");
    }
    memset((char *)&serveradd,0,sizeof(serveradd));
    memset((char *)&clientadd,0,sizeof(clientadd));
    if((sock=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        error("couldnt create socket.\n");
    }
    serveradd.sin_family=AF_INET;
    serveradd.sin_addr.s_addr=INADDR_ANY;
    serveradd.sin_port=htons(atoi(argv[1]));
    if((bind(sock,(struct sockaddr *)&serveradd,sizeof(serveradd)))<0)
    {
        error("binding failed.\n");
    }
    listen(sock,5);
    client=sizeof(clientadd);
    printf("waiting for a client to connect.\n");
    if((othersock=accept(sock,(struct sockaddr *)&clientadd,&client))<0)
    {
        error("connection failed.\n");
    }
    printf("connection sucessful.IP:%s\n",(char *)inet_ntoa(clientadd.sin_addr));
    char buffer[255];
    recv(othersock,buffer,sizeof(buffer),0);
    printf("%s\n",buffer);

}