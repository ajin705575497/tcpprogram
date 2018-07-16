#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
void ErrorHandling(char* message);

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET hSocket; //����SOCKET�����Ա���socket��������ֵ
	SOCKADDR_IN servAddr;

	char message[30];
	int strLen = 0;
	int idx = 0, readLen = 0;

	if (argc != 3)
	{
		printf("Usaage : %s <IP> <port> \n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("wsastartup() error");
	//����TCP�׽���
	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET)
		ErrorHandling("socket() error");
	
	struct in_addr s; // IPv4��ַ�ṹ��
	inet_pton(AF_INET, argv[1], (void *)&s);
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr = s;//servAddr.sin_addr.s_addr = inet_addr 
	servAddr.sin_port = htons(atoi(argv[2]));

	if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorHandling("connect() error");
	//whileѭ���е���recv������ȡ���ݣ�ÿ��1���ֽ�
	while (readLen = recv(hSocket, &message[idx++], 1, 0))
	{
		if (readLen == -1)
			ErrorHandling("read() error");

		strLen += readLen;//ÿ�ζ�ȡ1���ֽڣ����ÿ�μ�1
	}

	printf("Message from server : %s \n", message);
	printf("Function read call count: %d \n", strLen);

	closesocket(hSocket);
	WSACleanup();
	return 0;
}

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
