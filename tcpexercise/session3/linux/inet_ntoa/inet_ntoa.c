//将网络字节序整型转为字符型


#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char* argv[])
{
    struct sockaddr_in addr1, addr2;
    char* str_ptr;
    char str_arr[20];
    
    addr1.sin_addr.s_addr = htonl(0x1020304);
    addr2.sin_addr.s_addr = htonl(0x1010101);
    //向inet_ntoa函数传递结构体变量add1中的ip地址信息并调用该函数，返回字符串形式的ip地址 
    str_ptr = inet_ntoa(addr1.sin_addr);
    //浏览并复制上行中返回的ip地址信息
    strcpy(str_arr, str_ptr);
    printf("Dotted-Decimal notation1: %s \n", str_ptr);

    //再次调用inet_ntoa函数
    /*
    该函数将通过参数传入整数型IP地址转换为字符串格式并返回。但调用时需小心，返回值类型为char类型。
    返回字符串地址意味着字符串已保存到内存空间，单该函数未向程序员要求分配内存，而是在内部申请了内存
    并保存了字符串。也就是说，调用完该函数后，应立即将字符串信息复制到其他内存空间。因为，
    若再次调用inet_ntoa函数，则有可能覆盖之前保存的字符串信息。总之，再次调用inet_ntoa函数前返回
    的字符串地址值是有效的。若需要长期保存，则应将字符串复制到其他内存空间。
    */
    inet_ntoa(addr2.sin_addr);
    printf("Dotted-Decimal notation2: %s \n", str_ptr);
    printf("Dotted-Decimal notation3: %s \n", str_arr);
    
    return 0;
}
