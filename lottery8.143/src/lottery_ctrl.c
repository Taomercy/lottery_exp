#include <stdio.h>
#include "lottery_model.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "lottery_view.h"
#include "lottery_ctrl.h"


void lottery_main_ctrl(Userlink* userlink,Publink* publink, Buylink* buylink)//主控制层
{
	if(userlink == NULL)
	{
		printf("用户链表头节点为空!\n");
		return;
	}
	if(publink == NULL)
	{
		printf("发行彩票链表头节点为空！\n");
		return;
	}
	if(buylink == NULL)
	{
		printf("购买彩票链表头节点为空！\n");
		return;
	}
	Userlink* pos = (Userlink*)malloc(sizeof(Userlink));
	int choose = 0;
	int flag = 0;
	while(1)
	{
		sleep(1);
		system("clear");
		main_view();
		printf("请输入您的选择！\n");
		scanf("%d",&choose);
		if(getchar() != '\n')
		{
			printf("输入有误！\n");
			continue;
		}
		switch(choose)
		{
			case 1://用户注册
				user_regist(userlink);
				break;
			case 2://用户登录
				pos = login_user(userlink);
				if(pos == NULL)
				{
					break;
				}
				printf("登录成功！\n");
				enter_wait();
				user_ctrl(userlink,pos,buylink,publink);
				break;
			case 3://管理员登录
				flag = login_admin();
				if(flag == 0)
				{
					printf("登录失败！\n");
					break;
				}
				printf("登录成功！\n");
				enter_wait();
				admin_ctrl(userlink,publink);
				break;
			case 4://公正员登录
				flag = login_notary();
				if(flag == 0)
				{
					printf("登录失败!\n");
					break;
				}
				printf("登录成功！\n");
				notary_ctrl(userlink,publink,buylink);
				break;
			case 0://退出系统
				return;
			default:
				printf("输入错误，请重试！\n");
		}
	}
}

void admin_ctrl(Userlink* userlink, Publink* publink)//管理员控制层
{
	if(userlink == NULL)
	{
		printf("用户链表头节点为空!\n");
		return;
	}
	if(publink == NULL)
	{
		printf("发行彩票链表头节点为空！\n");
		return;
	}
	int choose = 0;
	while(1)
	{
		sleep(1);
		system("clear");
		admin_view();
		printf("请输入您的选择！\n");
		scanf("%d",&choose);
		if(getchar() != '\n')
		{
			printf("输入有误！\n");
			continue;
		}
		switch(choose)
		{
			case 1://查询用户信息
				find_one_user(userlink);
				break;
			case 2://发行彩票
				pub_lottery(publink);
				break;
			case 3://查看所有用户信息
				sort_way_ctrl(userlink);
				break;
			case 4://找回账户
				refind_account(userlink);
				userlink_save(userlink);
				break;
			case 0://返回上一级菜单
				return;
			default:
				printf("输入有误，请重新输入！\n");
				break;
		}
	}
}
void user_ctrl(Userlink* userlink, Userlink* pos, Buylink* buylink, Publink* publink)//用户控制层
{
	if(userlink == NULL)
	{
		printf("用户链表头节点为空!\n");
		return;
	}
	int choose = 0;
	while(1)
	{
		sleep(1);
		system("clear");
		user_view();
		printf("请输入您的选择！\n");
		scanf("%d",&choose);
		if(getchar() != '\n')
		{
			printf("输入有误！\n");
			continue;
		}
		switch(choose)
		{
			case 1://查看个人信息
				my_message(pos);
				break;
			case 2://修改密码
				change_password(userlink,pos);
				break;
			case 3://修改用户名
				change_name(userlink,pos);
				userlink_save(userlink);
				break;
			case 4://账户充值
				user_recharge(userlink,pos);
				userlink_save(userlink);
				break;
			case 5://购买彩票
				buy_lottery(pos,userlink,publink,buylink);
				break;
			case 6://查看购买记录
				find_my_history(pos,buylink);
				break;
			case 7://注销账户
				lock_account(pos);
				userlink_save(userlink);
				break;
			case 0://返回上一级菜单
				return;
			default:
				printf("输入有误，请重新输入！\n");
				break;
		}
	}
}
void sort_way_ctrl(Userlink* userlink)//排序方式
{
	if(userlink == NULL)
	{
		printf("用户链表头节点为空!\n");
		return;
	}
	int choose = 0;
	while(1)
	{
		sleep(1);
		system("clear");
		sort_all_user_view();
		printf("请输入您的选择！\n");
		scanf("%d",&choose);
		if(getchar() != '\n')
		{
			printf("输入有误！\n");
			continue;
		}
		switch(choose)
		{
			case 1://注册时间
				print_all_user(userlink);
				break;
			case 2://金额区间
				money_interval(userlink);
				break;
			case 3://查看注销账户
				locked_userlink(userlink);
				break;
			case 0://返回上一级菜单
				return;
			default:
				printf("输入错误！\n");
				break;
		}
	}
	
}

void notary_ctrl(Userlink* userlink,Publink* publink, Buylink* buylink)//公正员控制层
{
	if(publink == NULL)
	{
		printf("发行彩票链表头节点为空!\n");
		return;
	}
	int choose = 0;
	while(1)
	{
		sleep(1);
		system("clear");
		notary_view();
		printf("请输入您的选择！\n");
		scanf("%d",&choose);
		if(getchar() != '\n')
		{
			printf("输入有误！\n");
			continue;
		}
		switch(choose)
		{
			case 1://开奖
				run_lottery(userlink,publink,buylink);
				break;
			case 2://查询彩票信息
				check_lottery(publink,buylink);
				break;
			case 0://返回上一级菜单
				return;
			default:
				printf("输入错误！\n");
				break;
		}
	}
	
}
