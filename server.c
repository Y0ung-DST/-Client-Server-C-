#define _WIN32_IE 0x0501
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <shellapi.h>
#define PORT 9002


int	main(int argc, char **argv)
{
	char buff[256];
	int result = 0;
	WSADATA wsa;
	SOCKET listen_sock = INVALID_SOCKET;
	SOCKET data_sock = INVALID_SOCKET;

	NOTIFYICONDATA nid = {
		.hWnd        = GetDesktopWindow(),
		.cbSize      = sizeof(NOTIFYICONDATA),
		.uFlags      = NIF_INFO,
		.szInfo      = "",
		.uTimeout    = 10000,
		.szInfoTitle = "Server",
		.dwInfoFlags = NIIF_INFO
	};
	Shell_NotifyIcon(NIM_ADD, &nid);
	WSAStartup(0x22, &wsa);
	listen_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN sock_addr = {
		.sin_family      = AF_INET,
		.sin_addr.s_addr = INADDR_ANY,
		.sin_port        = htons(PORT)
	};
	bind(listen_sock, (SOCKADDR *)&sock_addr, sizeof(sock_addr));
	while (1)
	{
		listen(listen_sock, SOMAXCONN);
		data_sock = INVALID_SOCKET;
		data_sock = accept(listen_sock, NULL, NULL);
		while (1)
		{
			result = recv(data_sock, buff, sizeof(buff), 0);
			if (result == SOCKET_ERROR || result == 0)
				break;
			buff[sizeof(buff) - 1] = '\0';
			memcpy(nid.szInfo, buff, sizeof(buff));
			Shell_NotifyIcon(NIM_MODIFY, &nid);
		}
		closesocket(data_sock);
	}
	return (0);
}
