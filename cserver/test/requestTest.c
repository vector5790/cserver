#include"../request.h"
#include<stdio.h>
int main(){
	struct http_request request;
	char data[] = "POST / HTTP/1.1\n";
	parse_request(&request,data);
	printf("method=%s url=%s version=%s\n",request.method,request.url,request.version);
	return 0;
}

