#include "tools/utils.h"
struct http_request {
	char * method;
	char * url;
    	char * version;
    	char * body;
	struct Map* headers;
};


void parse_request(struct http_request * request,char * http_data);
