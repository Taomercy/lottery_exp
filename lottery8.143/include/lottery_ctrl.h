#ifndef LOTTERY_CTRL_H
#define LOTTERY_CTRL_H
#include "lottery_model.h"
void lottery_main_ctrl(Userlink* userlink,Publink* publink,Buylink* buylink);//主控制层

void admin_ctrl(Userlink* userlink, Publink* publink);//管理员控制层
void sort_way_ctrl(Userlink* userlink);//排序方式

void user_ctrl(Userlink* userlink, Userlink* pos, Buylink* buylink, Publink* publink);//用户控制层


void notary_ctrl(Userlink* userlink,Publink* publink,Buylink* buylink);//公正员控制层


#endif
