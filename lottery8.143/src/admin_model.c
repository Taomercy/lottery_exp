#include <stdio.h>
#include "lottery_model.h"
#include <string.h>
#include <time.h>
int login_admin(void)//管理员登录函数
{
	char str[20] = "admin";
	char input_name[20] = "";
	char input_password[20] = "";
	printf("请输入用户名：");
	getname(input_name);
	printf("请输入密码：");
	getPassword(input_password);
	if(strcmp(input_name,str) != 0 || strcmp(input_password,str) != 0)
	{
		return 0;
	}
	return 1;
}

void find_one_user(Userlink* userlink)//查看单个用户信息
{
	char name[20] = "";
	printf("请输入您要查看的用户：");
	getname(name);
	Userlink* person = userlink_select_node(userlink,name);
	if(person == NULL)
	{
		printf("此用户不存在!\n");
		return;
	}
	printf("姓名：%s\t余额：%.2f\t密码：%s\t注册时间：%s\n",person->data.name,person->data.money,person->data.password,person->data.time);
	printf("中奖次数：\n");
	printf("一等奖：%d\t二等奖：%d\t三等奖：%d\n",person->data.prob[1],person->data.prob[2],person->data.prob[3]);
	printf("中奖概率：\n");
	if(person->data.prob[0] == 0)
	{
		printf("一等奖：0.00%%\t二等奖：0.00%%\t三等奖：0.00%%\n");
	}
	else{
	printf("一等奖：%.2f%%\t二等奖：%.2f%%\t三等奖：%.2f%%\n",(float)person->data.prob[1]/person->data.prob[0],(float)person->data.prob[2]/person->data.prob[0],(float)person->data.prob[3]/person->data.prob[0]);
	}
	printf("中奖累计金额:%.2f\n",person->data.price);
	char lock[20] = "";
	if(person->data.lock == 0)
	{
		strcpy(lock,"正常");
	}
	else
	{
		strcpy(lock,"已注销");
	}
	printf("用户状态：%s\n",lock);
	getchar();
	enter_wait();
}


void print_all_user(Userlink* userlink)//输出用户信息,按注册时间
{
	if(userlink == NULL)
	{
		printf("用户链表头节点为空！\n");
		return;
	}
	userlink = userlink->next;
	while(userlink != NULL)
	{
		if(userlink->data.lock == -1)
		{
			userlink = userlink->next;
			continue;
		}
		printf("姓名：%s\t余额：%.2f\t\t\t\033[0;34m注册时间:%s\033[0;m\n",userlink->data.name,userlink->data.money,userlink->data.time);
		printf("中奖次数：\n");
		printf("一等奖：%d\t二等奖：%d\t三等奖：%d\n",userlink->data.prob[1],userlink->data.prob[2],userlink->data.prob[3]);
		printf("中奖概率：\n");
		if(userlink->data.prob[0] == 0)
		{
			printf("一等奖：0.00%%\t二等奖：0.00%%\t三等奖：0.00%%\n");
		}
		else{
		printf("一等奖：%.2f%%\t二等奖：%.2f%%\t三等奖：%.2f%%\n",(float)userlink->data.prob[1]/userlink->data.prob[0],(float)userlink->data.prob[2]/userlink->data.prob[0],(float)userlink->data.prob[3]/userlink->data.prob[0]);
		}
		printf("中奖累计金额:%.2f\n",userlink->data.price);
		printf("--------------------------------------------------------------------------\n");
		userlink = userlink->next;
	}
	enter_wait();
}


void money_interval(Userlink* userlink)//查看金额区间内外用户
{
	if(userlink == NULL)
	{
		printf("用户链表头节点为空!\n");
		return;
	}
	int len = 0,len1 = 0,len2 = 0;
	float low = 0.00, high = 0.00;
	int i = 0;
	printf("请输入金额下限：");
	scanf("%f",&low);
	printf("请输入金额上线：");
	scanf("%f",&high);
	if(getchar()!='\n' || low < 0 || high < 0 || low > high)
	{
		printf("输入错误！\n");
		return;
	}
	Userlink* temp = userlink;
	temp = temp->next;
	while(temp != NULL)
	{
		if(temp->data.money < low)
		{
			len1++;
		}
		if(temp->data.money >= low && temp->data.money <= high)
		{
			len2++;
		}
		++len;
		temp = temp->next;
	}
	sort_userlink(userlink,len);
	userlink = userlink->next;
	printf("姓名:\t金额:\n");
	while(userlink != NULL)
	{
		printf("%s\t%.2f\n",userlink->data.name,userlink->data.money);
		++i;
		if(i == len1 || i == len1 + len2)
		{
			printf("--------------------\n");
		}
		userlink = userlink->next;
	}
	enter_wait();
}

void locked_userlink(Userlink* userlink)//查看注销账户
{
	if(userlink == NULL)
	{
		printf("用户头节点空！\n");
		return;
	}
	userlink = userlink->next;
	while(userlink != NULL)
	{
		if(userlink->data.lock == -1)
		{	
			printf("姓名：%s\t余额：%.2f\t\t\t\033[0;31m注册时间:%s\033[0;m\n",userlink->data.name,userlink->data.money,userlink->data.time);
			printf("中奖次数：\n");
			printf("一等奖：%d\t二等奖：%d\t三等奖：%d\n",userlink->data.prob[1],userlink->data.prob[2],userlink->data.prob[3]);
			printf("中奖概率：\n");
			printf("一等奖：%.2f%%\t二等奖：%.2f%%\t三等奖：%.2f%%\n",(float)userlink->data.prob[1]/userlink->data.prob[0],(float)userlink->data.prob[2]/userlink->data.prob[0],(float)userlink->data.prob[3]/userlink->data.prob[0]);
			printf("中奖累计金额:%.2f\n",userlink->data.price);
			printf("--------------------------------------------------------------------------\n");
		}
		userlink = userlink->next;
	}
	enter_wait();
}

void sort_userlink(Userlink* userlink, int len)//排序
{
	if(userlink == NULL)
	{
		printf("用户链表头节点为空！\n");
		return;
	}
	int i = 0, j = 0;
	Userlink* pre = userlink;
	for(i = 0; i < len-1; ++i)
	{
		userlink = pre->next;
		for(j = 0; j < len-i-1; ++j)
		{
			if(userlink->data.money > userlink->next->data.money)
			{
				User data = userlink->data;
				userlink->data = userlink->next->data;
				userlink->next->data = data;
			}
			userlink = userlink->next;
		}
	}
}


void pub_lottery(Publink* publink)//发行彩票
{
	if(publink == NULL)
	{
		printf("发行彩票链表头节点为空！\n");
		return;
	}
	Publink* pubhead = publink;
	while(publink->next != NULL)//找到尾节点
	{
		publink = publink->next;
	}
	if(0 == strcmp(publink->data.state,"未开奖"))
	{
		printf("上一期彩票未开奖，暂时无法发行下一期彩票！\n");
		return;
	}
	Pub data;
	memset(&data,0,sizeof(Pub));
	time_t tt;
	char tmpbuf[40] = "";
	tt = time(NULL);
	strftime(tmpbuf,40,"%Y%m%d%H%M",localtime(&tt));
	char str[80] = "RAF";
	strcat(str,tmpbuf);
	strcpy(data.issue,str);
	printf("请输入彩票单价：");
	scanf("%f",&data.price);
	strcpy(data.state,"未开奖");
	data.sell_count = 0;
	if(publink->data.total_money < 0)
	{
		printf("当前奖池无金额，请输入奖池金额：");
		scanf("%f",&data.total_money);
	}
	else
	{
		data.total_money = publink->data.total_money;
	}
	data.num[0] = -1;
	data.num[1] = -1;
	data.num[2] = -1;
	publink_insert_after(publink,data);
	publink_save(pubhead);
	printf("彩票发行成功！\n");

}

void refind_account(Userlink* userlink)//用户找回
{
	if(userlink == NULL)
	{
		printf("用户链表头节点为空！\n");
		return;
	}
	char name[20] = "";
	printf("请输入要找回的用户名：");
	getname(name);
	userlink = userlink->next;
	while(userlink != NULL)
	{
		if(0 == strcmp(userlink->data.name,name))
		{
			if(userlink->data.lock == 0)
			{
				printf("此用户未注销！\n");
				return;
			}
			userlink->data.lock = 0;
			printf("找到此用户，找回成功！\n");
			return;
		}
		userlink = userlink->next;
	}
	printf("此用户不存在！\n");
	return;
}
