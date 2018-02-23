#include <stdio.h>
#include "lottery_ctrl.h"
#include "lottery_model.h"
#include <stdlib.h>


int main(void)
{
	Userlink* userlink = (Userlink*)calloc(1,sizeof(Userlink));//为用户链表创建头节点空间
	userlink_load(userlink);

	Publink* publink = (Publink*)calloc(1,sizeof(Publink));//为发行彩票链表创建头节点空间
	publink_load(publink);

	Buylink* buylink = (Buylink*)calloc(1,sizeof(Buylink));//为购买彩票链表创建头节点空间
	buylink_load(buylink);


	lottery_main_ctrl(userlink,publink,buylink);

	userlink_free(userlink);
	userlink = NULL;
	buylink_free(buylink);
	buylink = NULL;
	publink_free(publink);
	publink = NULL;


	return 0;
}
