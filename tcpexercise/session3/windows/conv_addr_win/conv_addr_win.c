//windows������ ip��ַ���ַ���ת��
#undef UNICODE
#undef _UNICODE
#include <stdio.h>
#include <WinSock2.h>

int main(int argc, char*argv[])
{
	char* strAddr = "203.211.218.102:9190";

	char strAddrBuf[50];
	SOCKADDR_IN servAddr;
	int size;

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("WSAStartup error");
		system("pause");
		exit(1);
	}

	size = sizeof(servAddr);
	//����ַ��Ϣ�ַ����ʵ�����ṹ�����
	WSAStringToAddress(strAddr, AF_INET, NULL, (SOCKADDR*)&servAddr, &size);

	size = sizeof(strAddrBuf);
	//���ṹ���еĵ�ַ��Ϣת�����ַ���
	WSAAddressToString((SOCKADDR*)&servAddr, sizeof(servAddr), NULL, strAddrBuf, &size);

	printf("Second conv result: %s \n", strAddrBuf);

	WSACleanup();
	system("pause");
	return 0;
}