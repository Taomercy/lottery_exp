#include <stdio.h>
#include "lottery_model.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void userlink_load(Userlink* userlink)//用户链表加载函数
{
	if(userlink == NULL)
	{
		printf("用户链表头节点为空！\n");
		return;
	}
	FILE* fp = fopen("userlink.bin","rb");
	if(fp == NULL)
	{
		system("touch userlink.bin");
		return ;
	}
	User data;
	memset(&data,0,sizeof(User));
	while(1)
	{
		int res = fread(&data,sizeof(User),1,fp);
		if(res < 1)
		{
			break;
		}
		userlink_insert_after(userlink,data);
	}
	printf("用户数据读取成功！\n");
	fclose(fp);
	fp = NULL;
}
void userlink_save(Userlink* userlink)//用户链表保存函数
{
	if(userlink == NULL)
	{
		printf("用户链表头节点为空！\n");
		return;
	}
	FILE* fp = fopen("userlink.bin","wb");
	if(fp == NULL)
	{
		printf("打开文件失败！\n");
		return;
	}
	userlink = userlink->next;
	while(userlink != NULL)
	{
		fwrite(&userlink->data,sizeof(User),1,fp);
		userlink = userlink->next;
	}
	printf("用户数据保存成功！\n");
	fclose(fp);
	fp = NULL;
}

void userlink_insert_after(Userlink* userlink, User data)//用户链表后插函数
{	
	if(userlink == NULL)
	{
		printf("用户链表头节点为空！\n");
		return;
	}
	Userlink* new_user_node = userlink_create_new_node(userlink,data);
	while(userlink->next != NULL)//找到尾节点
	{
		userlink = userlink->next;
	}
	userlink->next = new_user_node;//链接
}

Userlink* userlink_create_new_node(Userlink* userlink,User data)//用户链表节点创建函数
{
	Userlink* new_node = (Userlink*)calloc(1,sizeof(Userlink));//为新节点创建空间
	new_node->data = data;
	new_node->next = NULL;
	return new_node;
}
Userlink* userlink_select_node(Userlink* userlink, char name[])//用户链表姓名查询当前节点
{
	if(userlink == NULL)
	{
		printf("用户链表头节点为空！\n");
		return NULL;
	}
	userlink = userlink->next;
	while(userlink != NULL)
	{
		if(0 == strcmp(userlink->data.name,name))
		{
			return userlink;
		}
		userlink = userlink->next;
	}
	return NULL;
}

Userlink* userlink_select_front_node(Userlink* userlink, char name[])//用户链表姓名查询前一个节点
{	
	if(userlink == NULL)
	{
		printf("用户链表头节点为空！\n");
		return NULL;
	}
	Userlink* pre = userlink;
	userlink = userlink->next;
	while(userlink != NULL)
	{
		if(0 == strcmp(userlink->data.name,name))
		{
			return pre;
		}
		pre = userlink;
		userlink = userlink->next;
	}
	return NULL;
}

void userlink_free(Userlink* userlink)//释放
{
	if(userlink == NULL)
	{
		printf("userlink head is NULL!\n");
		return;
	}
	Userlink* pre = NULL;
	while(userlink != NULL)
	{
		pre = userlink->next;
		free(userlink);
		userlink = pre;
	}
}
