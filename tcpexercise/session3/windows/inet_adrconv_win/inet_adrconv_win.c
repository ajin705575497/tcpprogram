//ip地址与整形之间转换

#include <stdio.h>
#include <string.h>
#include <WinSock2.h>

void ErrorHandling(char* message);

int main(int argc, int argv[])
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		ErrorHandling("WSAStartup error!\n");
	}

	//inet_addr ip地址转整型
	{
		char *addr = "127.212.124.78";
		unsigned long conv_addr = inet_addr(addr);
		if (conv_addr == INADDR_NONE)
			printf("Error occured !\n");
		else
			printf("Network ordered integer addr : %#lx \n", conv_addr);
	}

	//inet_ntoa 整型转ip地址
	{
		struct sockaddr_in addr;
		char *strPtr;
		char strArr[20];

		addr.sin_addr.s_addr = htonl(0x1020304);
		strPtr = inet_ntoa(addr.sin_addr);
		strcpy(strArr, strPtr);
		printf("Dotted-Decimal notaion3 %s \n", strArr);
	}

	WSACleanup();
	system("pause");
	return 0;
}

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}