#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#define SERVER_ADDR "192.168.1.1"
//#define SERVER_ADDR "127.0.0.1" /* Forces IPv4 */
#define SERVER_PORT 9002

int	main(int ac, char **av) {
	char	buff [256];
	WSADATA wsa;
	WSAStartup(0x22, &wsa);
	Socket connect_sock = INVALID_SOCKET;
	connect_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_AIN sock_addr = {
		   .sin_family        = AF_INET;
		   .sin_addr.sin_addr = inet_addr(SERVER_ADDR);
		   .sin_port          = htons(SERVER_PORT);
	}
	connect(connect_sock, (SOCKADDR *)&sock_addr, sizeof(sock_addr));
	while (1)
	{
		fgets(buff, sizeof(buff), stdin);
		send(connect_sock, buff, strlen(buff) + 1, 0);
	}
	return (0);
}
