#include<errno.h>
#include<stdio.h>/*NULL*/
#include"utils.h"
#include<stdlib.h>/*free malloc calloc*/
#include<string.h>
void initItem(struct Item* listItem){
	listItem->next=NULL;
	listItem->val=NULL;
	listItem->key=NULL;
}
void initList(struct List* list){
	list->start=list->end=NULL;
	list->length=0;
}
struct Item* newItem(char* key,char* val){
	struct Item* item=(struct Item*)malloc(sizeof(struct Item));
	initItem(item);
	item->key=key;
	item->val=val;
	return item;
}
void listAppend(struct List* list,struct Item* item){
	item->next=NULL;	
	if(list->start==NULL){
		list->start=list->end=item;
	}
	else{
		list->end->next=item;
		list->end=item;
	}
	list->length++;
}
void listPrint(struct List* list){
	printf("[");
	struct Item* now=list->start;
	int i=0;	
	for(i=0;i<list->length;i++){
		if(i) printf(", ");
		printf("'%s'",now->val);
		now=now->next;
	}
	printf("]\n");		
}

/*Map*/

void initMap(struct Map* map){
	map->table_len=HashTableLen;
	map->item_cnt=0;
	int i;	
	for(i=0;i< map->table_len;i++){
		map->table[i]=NULL;
	}
}
void releaseMap(struct Map* map){
	int i;	
	for(i=0;i< map->table_len;i++){
		if(map->table[i]!=NULL){
			/*free*/
			struct Item* point=map->table[i]->start;
			struct Item* tmp=NULL;
			int j;			
			for(j=0;j< map->table[i]->length;j++){
				tmp=point->next;
				free(point);
				point=tmp;
			}
			free(map->table[i]);
			map->table[i]=NULL;
		}
	}
}
int hashCode(char* str){
	int code;
	int len=0;
	int maxLen=100;
	for(code=0;*str!='\0'&&len<maxLen;str++){
		code=code*31*(*str);
		len++;
	}
	return code%HashTableLen;
}
void mapPush(struct Map* map,struct Item* item){
	int index=hashCode(item->key);
	if(map->table[index]==NULL){
		struct List* list=malloc(sizeof(struct List));
		initList(list);
		if(list==NULL){
			perror("Error:out of storeage");
		}
		map->table[index]=list;
	}
	else{
		struct Item* _item;
		char* key=item->key;
		_item=map->table[index]->start;
		while(_item!=NULL){
			if(strcmp(key,_item->key)==0){
				_item->val=item->val;
				return;
			}
			_item=_item->next;
		}
	}
	listAppend(map->table[index],item);
	map->item_cnt++;
}
void mapPrint(struct Map* map){
	struct List* list;
	struct Item* item;
	int print_item_cnt=0;
	printf("{");
	int i;
	for(i=0;i<map->table_len;i++){
		list=map->table[i];
		if(list==NULL) continue;
		item=list->start;
		while(item!=NULL){
			printf("'%s': '%s'",item->key,(char*)(item->val));
			item=item->next;
			print_item_cnt++;
			if(print_item_cnt!=map->item_cnt){
				printf(", ");
			}
		}
	}
	printf("}\n");	
}

char* mapGet(struct Map* map,char* key){
	int index=hashCode(key);
	if(map->table[index]==NULL) return NULL;
	else{
		struct Item* item;
		item=map->table[index]->start;
		while(item!=NULL){
			if(strcmp(key,item->key)==0){
				return item->val;
			}
			item=item->next;
		}
	}
	return NULL;
}
