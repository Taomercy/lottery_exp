#include <stdio.h>
#include "lottery_model.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
void enter_wait(void)
{
	printf("按回车以继续...\n");
	while(getchar() != '\n')
	continue;
}

void user_regist(Userlink* userlink)//用户注册
{	
	if(userlink == NULL)
	{
		printf("用户链表头节点为空！\n");
		return;
	}
	char name[20];
	time_t tt;
	char tmpbuf[50];
//	char ch = '0';
	printf("请输入将要注册的用户名：");
	getname(name);
	if(0 == strcmp(name,"admin"))
	{
		printf("此用户名为管理员用户名，注册失败！\n");
		return;
	}
	if(0 == strcmp(name,"notary"))
	{
		printf("此用户名为公正员用户名，注册失败！\n");
		return;
	}
	Userlink* pos = userlink_select_node(userlink,name);
/*	while(1)
	{
		if(pos != NULL)
		{
			printf("此用户名已存在!\n");
			printf("放弃注册请按N/n,按其他以重新输入!\n");
			scanf("%c",&ch);
			if(ch == 'N' || ch == 'n')
			{
				return;
			}
			else
			{
				getchar();
				printf("请重新输入用户名：");
				scanf("%s",name);
				pos = userlink_select_node(userlink,name);
			}
		}
		if(pos == NULL)
		{
			printf("此用户名可用！\n");
			break;
		}
	}
*/
	if(pos != NULL)
	{
		printf("此用户名已存在，注册失败！\n");
		return;
	}
	User data;
	memset(&data,0,sizeof(User));
	char password[20] = "";
	strcpy(data.name,name);
	printf("请输入密码：");
	getPassword(data.password);
	printf("请再次输入密码：");
	getPassword(password);
	if(0 == strcmp(data.password,password))
	{
		strcpy(data.password,password);
		tt = time(NULL);
		strftime(tmpbuf,50,"%Y-%m-%d\t%H:%M:%S",localtime(&tt));
		strcpy(data.time,tmpbuf);
		userlink_insert_after(userlink,data);
		printf("注册成功！\n");
		userlink_save(userlink);
		enter_wait();
		return;
	}
	else
	{
		printf("两次密码不一致，注册失败！\n");
		return;
	}
}

Userlink* login_user(Userlink* userlink)//用户登录
{
	if(userlink == NULL)
	{
		printf("用户链表头节点为空！\n");
		return NULL;
	}
	srand(time(0));
	char name[20] = "";
	char password[20] = "";
	char keyboard[62] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	char idcode[5] = "";
	char lowcode[5] = "";
	char input_idcode[100] = "";
	int i = 0,j = 0, t = 0,k = 0;
	for(i = 0; i < 4;++i)
	{
		if(i % 2 != 0)
		{
			while(t < 100000)
			{
				if( t == 9999)
				{
					j = 52 + rand()%10;
					break;
				}
				++t;
			}
		}
		else
		{
			while(t < 10000)
			{
				if(t == 9999)
				{
					j = rand()%51;
					break;
				}
				++t;
			}
		}
		idcode[i] = keyboard[j];
		lowcode[i] = tolower(keyboard[j]);
	}
	printf("请输入您的用户名：");
	getname(name);
	Userlink* pos = userlink_select_node(userlink,name);
	if(pos == NULL)
	{
		printf("此用户不存在！\n");
		return NULL;
	}
	else if(pos->data.lock == -1)
	{
		printf("此账户已注销！登录失败！\n");
		return NULL;
	}
	else
	{
		k = 0;
		while(k < 3)
		{
			printf("请输入密码：");
			getPassword(password);
			if(0 == strcmp(pos->data.password,password))
			{	
				printf("\033[45;37m%s\033[0;m\n",idcode);
				printf("请输入验证码：");
				scanf("%s",input_idcode);
				for(i = 0; i < 100; ++i)
				{
					input_idcode[i] = tolower(input_idcode[i]);
				}
				if(0 == strcmp(input_idcode,lowcode))
				{
					return pos;
				}
				else
				{
					printf("验证码输入错误，登录失败！\n");
					return NULL;
				}
			}
			else
			{
				printf("密码输入错误，请重新输入！ \n");
				++k;
			}
		}
	printf("三次密码输入错误，登录失败！\n");
	return NULL;
	}
}

void my_message(Userlink* pos)//查看个人信息
{
	printf("姓名：%s\t密码：%s\t余额：%.2f\t注册时间：%s\n",pos->data.name,pos->data.password,pos->data.money,pos->data.time);
	printf("中奖次数：\n");
	printf("一等奖：%d\t二等奖：%d\t三等奖：%d\n",pos->data.prob[1],pos->data.prob[2],pos->data.prob[3]);
	printf("中奖概率：\n");
	if(pos->data.prob[0] == 0)
	{	
		printf("一等奖：0.00%%\t二等奖：0.00%%\t三等奖：0.00%%\n");
	}
	else
	{
		printf("一等奖：%.2f%%\t二等奖：%.2f%%\t三等奖：%.2f%%\n",(float)pos->data.prob[1]/pos->data.prob[0],(float)pos->data.prob[2]/pos->data.prob[0],(float)pos->data.prob[3]/pos->data.prob[0]);
	}
	printf("中奖累计金额:%.2f\n",pos->data.price);
	enter_wait();
}

void change_password(Userlink* userlink,Userlink* pos)//修改密码
{
	if(userlink == NULL)
	{
		printf("用户链表头节点为空！\n");
		return;
	}
	char password[20] = "";
	char new_password[20] = "";
	char new_password2[20] = "";
	printf("请输入旧密码：");
	getPassword(password);
	if(0 == strcmp(pos->data.password,password))
	{
		printf("请输入新密码：");
		getPassword(new_password);
		if(0 == strcmp(pos->data.password,new_password))
		{
			printf("新密码与旧密码一致,修改失败！\n");
			return;
		}
		printf("请再次输入新密码：");
		getPassword(new_password2);
		if(strcmp(new_password,new_password2) == 0)
		{
			strcpy(pos->data.password,new_password);
			userlink_save(userlink);
			printf("修改密码成功！\n");
			return;
		}
		else
		{
			printf("两次新密码不一致，修改失败！\n");
			return;
		}
	}
	else
	{
		printf("旧密码输入错误，修改失败！\n");
		return;
	}
}
void change_name(Userlink* userlink, Userlink* pos)//修改用户名
{
	char name[20]= "";
	printf("请输入新的用户名：");
	getname(name);
	userlink = userlink->next;
	while(userlink != NULL)
	{
		if(0 == strcmp(userlink->data.name,name))
		{
			printf("此用户名已存在！\n");
			return;
		}
		userlink = userlink->next;
	}
	strcpy(pos->data.name,name);
	printf("修改成功！\n");
}

void user_recharge(Userlink* userlink, Userlink* pos)//账户充值
{
	float money = 0.00;
	char ch = '0';
	while(1)
	{
		printf("请输入您要充值的金额：");
		scanf("%f",&money);
		if(getchar()!= '\n')
		{
			printf("输入错误，请重新输入！\n");
			break;
		}
		if(money <= 0.00)
		{
			printf("充值金额不小于0.01元，充值失败！\n");
			continue;
		}
		else
		{
			printf("您的充值金额为%.2f$\n确认请按Y/y,退出请按N/n,其他任意键重新输入：\n",money);
			scanf("%c",&ch);
			if(ch == 'Y' || ch == 'y')
			{
				pos->data.money = pos->data.money + money;
				printf("充值成功！\n");
				return;
			}
			if(ch == 'N' || ch == 'n')
			{
				return;
			}
		}
	}
}

void buy_lottery(Userlink* pos, Userlink* userlink,Publink* publink, Buylink* buylink)//购买彩票
{
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
	Publink* save_publink_head = publink;//
	int len = 0;
	while(publink->next != NULL)
	{
		len++;
		publink = publink->next;//找到发行彩票链表的尾节点
	}
	if(len == 0)
	{
		printf("彩票未发行，无法购买！\n");
		return;
	}
	if(0 == strcmp(publink->data.state,"已开奖"))
	{
		printf("本期彩票已开奖，暂无法购买！\n");
		return;
	}
	int i = 0,j = 0, k = 0;
	int choose = 0;
	srand(time(0));
	Buy data;//创建购买彩票结构体
	memset(&data,0,sizeof(Buy));
	strcpy(data.issue,publink->data.issue);//data.issue赋值
	data.id = 1000+publink->data.sell_count;//data.id赋值
	printf("请输入购买注数，上限为5注:\n");
	scanf("%d",&data.count);
	if(getchar()!= '\n')
	{
		printf("格式输入错误！\n");
		return;
	}
	if(pos->data.money < publink->data.price * data.count)
	{
		printf("余额不足，请充值！\n");
		return;
	}
	if(data.count <= 0 || data.count > 5)
	{
		printf("输入错误！\n");
		return;
	}
	pos->data.money = pos->data.money - publink->data.price * data.count;//个人余额支出
	pos->data.prob[0]++;
	data.money = 0;//data.money赋值
	strcpy(data.owner,pos->data.name);//data.owner赋值
	printf("请选择购买号码：");
	for(i = 0; i < data.count; )
	{
		printf("1.机选一注\t2.自选一注\n");
		scanf("%d",&choose);
		if(choose == 1)
		{
			for(j = 0; j < 3; ++j)
			{
				while(k < 100000)
				{
					if( k == 99999)
					{
						data.buynum[i][j] = rand()%100;
						break;
					}
					++k;
				}
			}
			printf("%d\t%d\t%d\n",data.buynum[i][0],data.buynum[i][1],data.buynum[i][2]);
			++i;
		}
		else if(choose == 2)
		{
			for(j = 0; j < 3; ++j)
			{
				printf("请输入一个0-99的数字：");
				scanf("%d",&data.buynum[i][j]);
				if(getchar() != '\n')
				{
					printf("格式输入错误！\n");
					return;
				}
				if(data.buynum[i][j] < 0 || data.buynum[i][j] > 99)
				{
					--i;
					printf("输入无效数字！\n");
					break;
				}
			}
			++i;
		}
		else
		{
			printf("选择错误,请重新选择！\n");
			continue;
		}
	}
	buylink_insert_after(buylink,data);
	publink->data.total_money = publink->data.total_money + publink->data.price * data.count;//奖池金额累计
	publink->data.sell_count ++;//彩票售出数量+1
	printf("购买号码完成！\n");
	printf("当前余额为：%.2f\n",pos->data.money);
	printf("*********************************\n");
	printf("  期号：    %s\n",data.issue);
	printf("  ID:       %d\n",data.id);
	printf("  购买者：  %s\n",data.owner);
	printf("  购买注数：%d\n",data.count);
	printf("  购买号码：  \n");
	for(i = 0; i < data.count; ++i)
	{
		printf("%d\t%d\t%d\n",data.buynum[i][0],data.buynum[i][1],data.buynum[i][2]);
	}
	printf("*********************************\n");
	getchar();
	enter_wait();
	buylink_save(buylink);
	userlink_save(userlink);
	publink_save(save_publink_head);
}


void find_my_history(Userlink* pos,Buylink* buylink)//查询个人历史记录
{
	if(buylink == NULL)
	{
		printf("购买彩票头节点为空！\n");
		return;
	}
	int i = 0;
	buylink = buylink->next;
	while(buylink != NULL)
	{
		if(0 == strcmp(buylink->data.owner,pos->data.name))
		{	
			printf("*********************************\n");
			printf("  期号：    %s\n",buylink->data.issue);
			printf("  ID:       %d\n",buylink->data.id);
			printf("  购买者：  %s\n",buylink->data.owner);
			printf("  购买注数：%d\n",buylink->data.count);
			printf("  购买号码：  \n");
			for(i = 0; i < buylink->data.count; ++i)
			{
				printf("  %d\t%d\t%d\n",buylink->data.buynum[i][0],buylink->data.buynum[i][1],buylink->data.buynum[i][2]);
			}
			printf("  此彩票中奖金额：%.2f\n",buylink->data.money);
			printf("*********************************\n");
		}
		buylink = buylink->next;
	}
	enter_wait();
}

void lock_account(Userlink* pos)//账户注销
{
	char ch = '0';
	printf("确认注销请按Y/y\n");
	scanf("%c",&ch);
	if(ch == 'Y' || ch == 'y')
	{
		pos->data.lock = -1;
		printf("注销账户成功！\n");
	}
	else
	{
		printf("取消账户注销！\n");
	}
	return;

}
