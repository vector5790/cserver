#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#define MAXREQUESTLEN 50000

#include "response.h"
void initString(char * c, int length) {
    int i = 0;
    while(i < length) {
        *(c + i) = '\0';  
        i++;
    }
}
int main() {
    int server_sockfd, client_sockfd;
    socklen_t server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0); //  创建socket，选择地址类型为网络地址，选择 TCP 通信

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");  // 设置网络地址的ip, inet_addr 会自动 转为 网络字节顺序
    server_address.sin_port = htons(9734);    //  设置端口号，注意这里的 htons 方法 
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

    listen(server_sockfd, 5);
    while(1) {
        char ch[MAXREQUESTLEN];
	initString(ch,MAXREQUESTLEN);
        char send_str[] = "hello world !\n";  // 准备给连接过来的客户端发送的字符串
        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd,
        (struct sockaddr *)&client_address, &client_len);
        
	read(client_sockfd, &ch, MAXREQUESTLEN);    // 接收 客户端传来的字符
        printf("%s", ch);     //  打印我们接收到的字符
        struct http_request request;
	struct Map headers;
	request.headers=&headers;
	parse_request(&request,ch);
	FILE* fp=fdopen(client_sockfd,"w+");
	doResponse(&request,fp);
	fflush(fp);
	fclose(fp);
	/*write(client_sockfd, &send_str, sizeof(send_str)/sizeof(send_str[0]));   // 向客户端发送数据，这里的 read write 和 和文件读写时没什么区别 
	*/
        close(client_sockfd);
    }
}
