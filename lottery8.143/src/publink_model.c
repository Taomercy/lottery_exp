#include <stdio.h>
#include "lottery_model.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


void publink_load(Publink* publink)//发行彩票链表加载函数
{
	if(publink == NULL)
	{
		printf("发行彩票头节点为空!\n");
		return;
	}
	FILE* fp = fopen("publink.bin","rb");
	if(fp == NULL)
	{
		system("touch publink.bin");
		return ;
	}
	Pub data;
	memset(&data,0,sizeof(Pub));
	while(1)
	{
		int res = fread(&data,sizeof(Pub),1,fp);
		if(res < 1)
		{
			break;
		}
		publink_insert_after(publink,data);
	}
	printf("发行彩票数据读取成功！\n");
	fclose(fp);
	fp = NULL;
}
void publink_save(Publink* publink)//发行彩票链表保存函数
{
	if(publink == NULL)
	{
		printf("发行彩票头节点为空！\n");
		return;
	}
	FILE* fp = fopen("publink.bin","wb");
	if(fp == NULL)
	{
		printf("打开文件失败！\n");
		return;
	}
	publink = publink->next;
	while(publink != NULL)
	{
		fwrite(&publink->data,sizeof(Pub),1,fp);
		publink = publink->next;
	}
	printf("发行彩票数据保存成功！\n");
	fclose(fp);
	fp = NULL;
}

void publink_insert_after(Publink* publink, Pub data)//发行彩票链表后插函数
{
	if(publink == NULL)
	{
		printf("发行彩票头节点为空！\n");
		return;
	}
	Publink* new_pub_node = publink_create_new_node(publink,data);
	while(publink->next != NULL)//找到尾节点
	{
		publink = publink->next;
	}
	publink->next = new_pub_node;//链接
}

Publink* publink_create_new_node(Publink* publink,Pub data)//发行彩票链表节点创建函数
{
	Publink* new_node = (Publink*)calloc(1,sizeof(Publink));//为新节点创建空间
	new_node->data = data;
	new_node->next = NULL;
	return new_node;
}
void publink_free(Publink* publink)//释放
{
	if(publink == NULL)
	{
		printf("publink head is NULL!\n");
		return;
	}
	Publink* pre = NULL;
	while(publink != NULL)
	{
		pre = publink->next;
		free(publink);
		publink = pre;
	}
}
/*
Publink* publink_select_node(Publink* publink, char issue[])//发行彩票链表期号查询当前节点
{	
	if(publink == NULL)
	{
		printf("发行彩票头节点为空！\n");
		return NULL;
	}
	publink = publink->next;
	while(publink != NULL)
	{
		if(0 == strcmp(publink->data.issue,issue))
		{
			return publink;
		}
		publink = publink->next;
	}
	return NULL;
}

Publink* publink_select_front_node(Publink* publink, char issue[])//发行彩票链表期号查询前一个节点
{
	if(publink == NULL)
	{
		printf("发行彩票头节点为空！\n");
		return NULL;
	}
	Publink* pre = publink;
	publink = publink->next;
	while(publink != NULL)
	{
		if(0 == strcmp(publink->data.issue,issue))
		{
			return pre;
		}
		pre = publink;
		publink = publink->next;
	}
	return NULL;
}
*/
