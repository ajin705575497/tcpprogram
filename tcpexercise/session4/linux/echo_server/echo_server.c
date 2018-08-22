#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char* message);

int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;
    char message[BUF_SIZE];
    int str_len, i;
    
    struct sockaddr_in serv_addr, clnt_adr;
    socklen_t clnt_adr_sz;
    
    if(argc != 2)
    {
        printf("usage :%s <port> \n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
    {
        error_handling("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind() error ");
    
    if(listen(serv_sock, 5) == -1)
	error_handling("listen() error");
    
    clnt_adr_sz = sizeof(clnt_adr);
    /*循环处理5个客户端连接，共调用5次accept函数，一次向5个客户端提供服务*/
    for(i = 0; i< 5; i++)
    {
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
        if(clnt_sock == -1)
            error_handling("accept() error");
        else
            printf("connected client %d \n", i+1);
        /*回声服务器  将受到的信息原样返回给客户端*/
        while((str_len = read(clnt_sock, message, BUF_SIZE)) != 0)
            write(clnt_sock, message, str_len);
        /*关闭客户端套接字 向连接的相应套接字发送EOF*/
        close(clnt_sock);
    }
    /*关闭服务端套接字*/
    close(serv_sock);
    return 0;
} 


void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
