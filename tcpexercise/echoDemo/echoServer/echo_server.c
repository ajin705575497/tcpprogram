/*
echoserver demo server source
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

void error_handling(char *message);

int main(int argc, char *argv[])
{
    // init
    int serv_sock, clnt_sock;
    char message[BUF_SIZE];
    int str_len, i;
  
    struct sockadd_in serv_adr, clnt_adr;
   socklen_t clnt_adr_sz;
}
