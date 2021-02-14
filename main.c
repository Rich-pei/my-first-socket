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
    int sock, othersock=0, pnum;
    struct sockaddr_in serveradd, clientadd;
    socklen_t client;
    if (argc < 2)
    {
        error("missing pnum\n");
    }
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        error("couldnt open socket\n");
    }
    memset(&serveradd, 0, sizeof(serveradd));
    serveradd.sin_family = AF_INET;
    serveradd.sin_addr.s_addr = INADDR_ANY;
    serveradd.sin_port = htons((uint16_t)atoi(argv[1]));

    if (bind(sock, (struct sockaddr *)&serveradd, sizeof(serveradd)) < 0)
    {
        error("couldnt bind.\n");
    }
    listen(sock,5);
    printf("waiting for a client to connect...\n");
    client=sizeof(clientadd);
    if ((othersock=accept(sock,(struct sockaddr *)&clientadd,&client)) < 0)
    {
        error("client couldnt connect to you.\n");
    }
    printf("client sucessfly connected. IP:%s\n", inet_ntoa(clientadd.sin_addr));
    char *buffer = {"hello"};
    send(othersock, buffer, sizeof(buffer), 0);
}