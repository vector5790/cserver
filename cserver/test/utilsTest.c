#include<stdio.h>
#include<assert.h>
#include "../tools/utils.h"
void listAppendTest(){
	struct List list_instance;
	initList(&list_instance);
	struct List* list=&list_instance;

	struct Item item_instance;
	initItem(&item_instance);
	struct Item* item=&item_instance;
	item->val="hello world";
	
	struct Item item_instance2;
	initItem(&item_instance2);
	struct Item* item2=&item_instance2;
	item2->val="nice to meet you";
	
	assert(list->length==0);
	listAppend(list,item);
	assert(list->length==1);
	listAppend(list,item2);
	listPrint(list);
	printf("TEST OK\n");	
}
/*void mapPushTest(){
	struct Map map_instance;
	initMap(&map_instance);
	struct Map* map=&map_instance;
	
	struct Item item_instance;
	initItem(&item_instance);
	struct Item* item=&item_instance;
	item->key="h";
	item->val="hello world";
	mapPush(map,item);
	mapPrint(map);
	
	struct Item item_instance2;
	initItem(&item_instance2);
	struct Item* item2=&item_instance2;
	item2->key="h2";
	item2->val="nice to meet you";
	mapPush(map,item2);
	mapPrint(map);

	struct Item item_instance3;
	initItem(&item_instance3);
	struct Item* item3=&item_instance3;
	item3->key="h2";
	item3->val="nice to meet you too";
	mapPush(map,item3);
	mapPrint(map);
	
	printf("the value for the key is %s: %s, %s: %s, %s: %s\n","h",mapGet(map,"h"),
			"h2",mapGet(map,"h2"),"h3",mapGet(map,"h3"));
		
	releaseMap(map);		
}*/
void mapPushTest() {
    struct Map map_instance;
    initMap(&map_instance);
    struct Map* map = &map_instance;
    
    char* key = "h";
    char* val = "hello world";
    struct Item* item = newItem(key,val); 
    mapPush(map, item);
    mapPrint(map);

    key = "h2";
    val = "nice to meet you too";
    struct Item* item2 = newItem(key,val); 
    mapPush(map, item2);
    mapPrint(map);

    key = "h2";
    val = "nice to meet you too too";
    struct Item* item3 = newItem(key,val); 
    mapPush(map, item3);
    mapPrint(map);
    printf("the value fo the key is  %s: %s, %s: %s %s: %s\n",
             "h", mapGet(map, "h"), 
             "h2", mapGet(map, "h2"), 
             "h3", mapGet(map, "h3"));
    
    
    releaseMap(map);
}
int main(){
	//listAppendTest();
	mapPushTest();
}
