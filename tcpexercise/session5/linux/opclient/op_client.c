#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
//待算数字的字节数和运算结果的字节数设置为常数
#define BUF_SIZE 1024
#define RLT_SIZE 4
#define OPSZ 4

void error_handling(char* message);

int main(int argc, char* argv[])
{
    int sock;
    //为首发数据准备内存空间，需要数据累计到一定程度后再首发，因此通过数组创建
    char opmsg[BUF_SIZE];
    int result, opnd_cnt, i;
    struct sockaddr_in serv_adr;
    if(argc != 3)
    {
         printf("Usage :%s <ip> <port> \n", argv[0]);
         exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1)
         error_handling("socket() error");
    
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));
  
    if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("connect() error");
    else
        puts("connects....");
    
    fputs("Operand count: ",stdout);
    //从程序用户的输入中得到待算数个数后，保存至数组opmsg。强制转换成char类型，因为协议规定待算数个数
    //应通过1字节整数型传递，因此不能超过1字节整数型能表示的范围。
    scanf("%d", &opnd_cnt);
    opmsg[0] = (char)opnd_cnt;


    for(i = 0; i < opnd_cnt; i++)
    { 
       //从程序用户的输入中得到待算整数，保存到数组中，4字节的int型整数要保存到char数组，因此转换成int指针类型
        printf("Operand %d: ", i+1);
        scanf("%d",(int*)&opmsg[i*OPSZ+1]);
    }
    //下面需输入字符，在此之前调用fgetc函数删掉缓冲中的字符 \n
    fgetc(stdin);
    fputs("Operator: ", stdout);
    //输入运算符并保存到数组中
    scanf("%c", &opmsg[opnd_cnt*OPSZ+1]);
    //调用write一次性传输数组中的运算相关信息
    write(sock, opmsg, opnd_cnt*OPSZ+2);
    //保存服务器端传输的运算结果.待接收的数组长度为4字节
    read(sock, &result, RLT_SIZE);
    
    printf("Operation result: %d \n", result);
    close(sock);
    return 0;
}

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}


