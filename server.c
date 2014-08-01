#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFSIZE 1024

int main( int argc, char** argv )
{
    int serv_sock;
    int clnt_sock;

    char message[BUFSIZE];
    int str_len;

    struct sockaddr_in serv_addr = { 0, };
    struct sockaddr_in clnt_addr = { 0, };

    int clnt_addr_size;

    if(argc != 2 )
    {
        printf("Usage : %s <port>\n", argv[0]);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
    {
        printf("socket error\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if( bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1 )
    {
        printf("bind error \n");
        return -1;
    }

    if( listen(serv_sock, 5) == -1 )
    {
        printf("listen error \n");
        return -1;
    }

    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    if( -1 == clnt_sock )
    {
        printf("accept error \n");
        return -1;
    }

    printf("accept success clnt_sock = %d\n", clnt_sock);

    sleep(5);

    str_len = read(clnt_sock, message, BUFSIZE);
    printf("read bytes = %d\n", str_len );


    write(clnt_sock, message, str_len);

    close(clnt_sock);
    close(serv_sock);



    return 0;
}






