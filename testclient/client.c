#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int main( int argc, char** argv )
{
	int sock;
	int str_len, i;
	struct sockaddr_in serv_addr={ 0, };

	char message[30];

	if ( argc < 3 )
	{
		printf("Usage : %s <ip> <port>\n", argv[0]);
		return -1;
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock != -1)
	{
		printf("socket open error\n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	if( connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1 )
	{
		printf("connect error\n");
		return -1;
	}

	str_len = read(sock, message, sizeof(message)-1 );
	if( str_len <= 0 )
	{
		printf("read error \n");
		return -1;
	}

	message[str_len] = '\0';

	printf("message from server : %s\n", message);

	close(sock);

	return 0;
}



	

