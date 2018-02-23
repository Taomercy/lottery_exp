#include <stdio.h>
#include "lottery_model.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>

int login_notary(void)//公正员登录
{
	char str[20] = "notary";
	char input_name[20] = "";
	char input_password[20] = "";
	printf("请输入用户名：");
	getname(input_name);
	printf("请输入密码：");
	getPassword(input_password);
	if(0 != strcmp(input_name,str) || 0 != strcmp(input_password,str))
	{
		return 0;
	}
	return 1;
}


void check_lottery(Publink* publink, Buylink* buylink)//查询彩票信息
{
	if(publink == NULL)
	{
		printf("发行彩票头节点为空！\n");
		return;
	}
	if(buylink == NULL)
	{
		printf("购买彩票链表头节点为空！\n");
	}
	int i = 0;
	publink = publink->next;
	printf("\033[0;32m期号：\t\t\t单价：\t\t开奖状态：\t售出总数：\t奖池金额：\033[0;m\n");
	while(publink != NULL)
	{
		printf("\033[0;35m=================================================================\033[0;m\n");
		printf("\033[0;34m%s\t\t%.2f\t\t%s\t\t%d\t\t%.2f\033[0;m\n",publink->data.issue,publink->data.price,\
			publink->data.state,publink->data.sell_count,publink->data.total_money);
		printf("中奖号码：\n");
		if(0 == strcmp(publink->data.state,"未开奖"))
		{
			printf("* * *\n");
		}
		else
		{
			for(i = 0; i < 3; ++i)
			{
				printf("\033[0;31m%d \033[0;m",publink->data.num[i]);
			}
		}
		printf("\n");
		if(0 == strcmp(publink->data.state,"未开奖"))
		{
			printf("\033[0;35m----------------------------------------------\033[0;m\n");
			printf("彩票id：\t购买人：\t购买注数：\n");
			buylink = buylink->next;
			while(buylink != NULL)
			{
				if(0 == strcmp(publink->data.issue,buylink->data.issue))
				{
					printf("\033[0;34m%d\t\t%s\t\t%d\033[0;m\n",buylink->data.id,buylink->data.owner,buylink->data.count);
				}
				buylink = buylink->next;
			}
		}
		publink = publink->next;
	}
	enter_wait();
}


void run_lottery(Userlink* userlink,Publink* publink, Buylink* buylink)//开奖
{
	if(userlink == NULL)
	{
		printf("用户链表头节点为空！\n");
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
	Userlink* userhead = userlink;
	Publink* pubhead = publink;
	Buylink* buyhead = buylink;
	int len = 0;
	while(publink->next != NULL)
	{
		len++;
		publink = publink->next;//找到尾节点
	}
	if(len == 0)
	{
		printf("彩票未发行，无法开奖！\n");
		return;
	}
	if(0 == strcmp(publink->data.state,"已开奖"))
	{
		printf("本期彩票已开奖，暂无法开奖！\n");
		return;
	}
	int lucky_num[3] = {-1,-1,-1};
	int* p_lucky_num = lucky_num;
	int i = 0;
	printf("开奖系统已启动...\n");
	enter_wait();
	create_lucky_num(p_lucky_num);//用于产生中奖号码
//-----------------------------------------------------

	printf("本期中奖号码为：\n");
	for(i = 0; i < 3; ++i)
	{
		printf("%d\t",lucky_num[i]);
	}
	printf("\n");
	enter_wait();

	strcpy(publink->data.state,"已开奖");
	for(i = 0; i < 3; ++i)//将中奖号码写入发行彩票
	{
		publink->data.num[i] = lucky_num[i];
	}
	printf("\033[0;34m%s期彩票共售出%d注,奖池金额为：%.2f\033[0;m\n",publink->data.issue,publink->data.sell_count,publink->data.total_money);
	match_num(userlink,publink,buylink,p_lucky_num);//号码匹配与奖金发放
	enter_wait();
	userlink_save(userhead);
	publink_save(pubhead);
	buylink_save(buyhead);
//------------------------------------------------------
}

void create_lucky_num(int* p_lucky_num)//用于产生中奖号码
{
	srand(time(0));
	int choose = 0;
	int random_num = 0;
	int error_num = 0;
	int t = 0, i = 0;
	while(1)
		{
			printf("请选择：\n1.机选随机数\n2.手选随机数\n");
			scanf("%d",&choose);
			getchar();
			if(choose == 1)
			{
				for(i = 0; i < 3; )
				{	
					t = 0;
					printf("将随机产生第%d个数字!\n",i+1);
					while(t < 100000)
					{
						printf("%d\r",rand()%100);
						if(t == 99999)
						{
							random_num = rand()%100;
							printf("%d\n",random_num);
							enter_wait();
							break;
						}
						++t;
					}
					*(p_lucky_num+i) = random_num;
					++i;
				}
				break;
			}
			else if(choose == 2)
			{
				for(i = 0; i < 3; ++i)
				{
					printf("请输入第%d个数字：",i+1);
					scanf("%d",&random_num);
					*(p_lucky_num+i) = random_num;
				}
				break;
			}	
			else
			{
				printf("选择错误，请重新选择！\n");
				++error_num;
				if(error_num == 3)
				{
					printf("三次选择错误！开奖失败！\n");
					return;
				}
				continue;
			}
			break;
		}
}


void match_num(Userlink* userlink,Publink* publink, Buylink* buylink, int* p_lucky_num)//号码匹配与奖金发放
{
	int i = 0;
	int j = 0;
	int lucky_person_num = 0;
	int temp_price = 0;
	int res_price = 0;
	float price_money = 0.00;
	float temp_total_money = publink->data.total_money;
	Userlink* save = userlink;
	buylink = buylink->next;//遍历购买链表匹配期号
	while(buylink != NULL)
	{
		if(0 == strcmp(publink->data.issue,buylink->data.issue))
		{
			temp_price = 0;
			res_price = 0;
			price_money = 0;
			for(i = 0; i < buylink->data.count; ++i)//匹配一个购买彩票链表节点
			{
				for(j = 0; j < 3; ++j)
				{
					if(*(p_lucky_num+j) == buylink->data.buynum[i][j])//匹配一个购买号码
					{
						temp_price++;
					}
				}
				if(res_price < temp_price)
				{
					res_price = temp_price;
				}
				if(res_price == 3)
				{
					break;
				}
			}
			//----------------------------------------号码匹配完成,结果为0，1，2，3
			userlink = save;
			userlink = userlink->next;
			while(userlink != NULL)//寻找当前彩票节点购买者信息
			{
				if(0 == strcmp(buylink->data.owner,userlink->data.name) || userlink->data.lock != -1)
				{
					break;
				}
				userlink = userlink->next;
			}
			if(res_price == 3)//一等奖奖励发放
			{
				price_money = 0.1*temp_total_money*buylink->data.count;
				publink->data.total_money -= price_money;
				userlink->data.money += price_money;
				userlink->data.prob[1]++;
				userlink->data.price += price_money;
			}
			else if(res_price == 2)//二等奖奖励发放
			{
				price_money = 0.05*temp_total_money*buylink->data.count;
				publink->data.total_money -= price_money;
				userlink->data.money += price_money;
				userlink->data.prob[2]++;
				userlink->data.price += price_money;
			}
			else if(res_price == 1)//三等奖奖励发放
			{	
				price_money = 0.01*temp_total_money*buylink->data.count;
				publink->data.total_money -= price_money;
				userlink->data.money += price_money;
				userlink->data.prob[3]++;
				userlink->data.price += price_money;
			}
			else
			{
				buylink->data.money = 0;
			}
			if(res_price > 0)
			{
				printf("中奖人：%s\t中奖等级：%d等奖\t中奖金额：%.2f\t彩票ID：%d\n",userlink->data.name,4-res_price,price_money,buylink->data.id);
				lucky_person_num++;
			}
			if(price_money > 0)
			{
				buylink->data.money = price_money;
			}
		}
		buylink = buylink->next;
	}
	if(lucky_person_num == 0)
	{
		printf("本期彩票无人中奖！\n");
	}
	printf("奖池余额：%.2f\n",publink->data.total_money);
}

