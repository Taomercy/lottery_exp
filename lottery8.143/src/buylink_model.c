#include <stdio.h>
#include "lottery_model.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void buylink_load(Buylink* buylink)//购买彩票链表加载函数
{
	if(buylink == NULL)
	{
		printf("购买彩票链表头节点为空！\n");
		return;
	}
	FILE* fp = fopen("buylink.bin","rb");
	if(fp == NULL)
	{
		system("touch buylink.bin");
		return ;
	}
	Buy data;
	memset(&data,0,sizeof(Buy));
	while(1)
	{
		int res = fread(&data,sizeof(Buy),1,fp);
		if(res < 1)
		{
			break;
		}
		buylink_insert_after(buylink,data);
	}
	printf("购买彩票数据读取成功！\n");
	fclose(fp);
	fp = NULL;
}
void buylink_save(Buylink* buylink)//购买彩票链表保存函数
{	
	if(buylink == NULL)
	{
		printf("购买彩票链表头节点为空！\n");
		return;
	}
	FILE* fp = fopen("buylink.bin","wb");
	if(fp == NULL)
	{
		printf("打开文件失败！\n");
		return;
	}
	buylink = buylink->next;
	while(buylink != NULL)
	{
		fwrite(&buylink->data,sizeof(Buy),1,fp);
		buylink = buylink->next;
	}
	printf("购买彩票数据保存成功！\n");
	fclose(fp);
	fp = NULL;
}

void buylink_insert_after(Buylink* buylink, Buy data)//购买彩票链表后插函数
{	
	if(buylink == NULL)
	{
		printf("购买彩票链表头节点为空！\n");
		return;
	}
	Buylink* new_buy_node = buylink_create_new_node(buylink,data);
	while(buylink->next != NULL)//找到尾节点
	{
		buylink = buylink->next;
	}
	buylink->next = new_buy_node;//链接
}

Buylink* buylink_create_new_node(Buylink* buylink,Buy data)//购买彩票链表节点创建函数
{
	Buylink* new_node = (Buylink*)calloc(1,sizeof(Buylink));//为新节点创建空间
	new_node->data = data;
	new_node->next = NULL;
	return new_node;

}
void buylink_free(Buylink* buylink)//释放
{
	if(buylink == NULL)
	{
		printf("buylink head is NULL!\n");
		return;
	}
	Buylink* pre = NULL;
	while(buylink != NULL)
	{
		pre = buylink->next;
		free(buylink);
		buylink = pre;
	}
}

/*
Buylink* buylink_select_node(Buylink* buylink, int id)//购买彩票链表姓名查询当前节点
{		
	if(buylink == NULL)
	{
		printf("购买彩票链表头节点为空！\n");
		return NULL;
	}
	buylink = buylink->next;
	while(buylink != NULL)
	{
		if(buylink->data.id == id)
		{
			return buylink;
		}
		buylink = buylink->next;
	}
	return NULL;
}

Buylink* buylink_select_front_node(Buylink* buylink, int id)//购买彩票链表姓名查询前一个节点
{	
	if(buylink == NULL)
	{
		printf("购买彩票链表头节点为空！\n");
		return NULL;
	}
	Buylink* pre = buylink;
	buylink = buylink->next;
	while(buylink != NULL)
	{
		if(buylink->data.id == id))
		{
			return pre;
		}
		pre = buylink;
		buylink = buylink->next;
	}
}

*/
