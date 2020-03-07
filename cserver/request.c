#include "request.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void parse_request(struct http_request * request,char* http_data){
	char* start=http_data;
	char* method=start;
	char* url=0;
	char* version=0;
	for(;*start&&*start!='\r';start++){
		if(*start==' '){
			if(url==0){
				url=start+1;
			}
			else version=start+1;
			*start='\0';
		}
	}
	*start='\0';// \r -> \0
	start++;//skip \n
	request->method=method;
	request->url=url;
	request->version=version;
/*******************second line *header***************/
	start++;
	initMap(request->headers);
	char* line=start;
	//char* key;
	//char* value;
	while(*line!='\r' && *line!='\0'){
		
		while(*(start++)!=':');
		*(start-1)='\0';
		char* key=line;
		char* value=start;
		//char* key="a";
		//char* value="b";		
		while(start++,*start!='\0'&&*start!='\r');
		*start++='\0';
		start++;//skip \n
		line=start;
		
		struct Item* item=newItem(key,value);
		mapPush(request->headers,item);
	}
/***************last line*****/
	if(*line =='\r'){
		//char* tmp="Content-Length";		
		char* len_str=mapGet(request->headers,"Content-Length");
		if(len_str!=NULL){	
			int len=atoi(len_str);
			line=line+2;
			*(line+len)='\0';
			request->body=line;
		}
	}
	/*print message of request*/
	printf("\n---------------------------\n");
	printf("method is: %s \n",request->method);
	printf("url is: %s \n",request->url);
	printf("http version is : %s \n",request->version);
	printf("the headers are :\n");
	mapPrint(request->headers);
	printf("body is %s \n",request->body);
	printf("---------------------------\n");
	return;
}
