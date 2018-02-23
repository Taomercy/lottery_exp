#ifndef LOTTERY_MODEL_H
#define LOTTERY_MODEL_H
/*****用户结构体单元声明*****/
typedef struct user{
	char name[20];
	char password[20];
	float money;
	char time[50];
	int prob[4];//购买总数，一等奖次数，二等奖次数，三等奖次数
	float price;//累计中奖金额
	int lock;//账户状态
}User;
typedef struct userlink{
	User data;
	struct userlink* next;
}Userlink;
/*****购买彩票结构体单元声明*****/
typedef struct buy{
	char issue[80];//期号
	int id;
	int buynum[5][3];//购买号码
	int count;//购买注数
	char owner[20];// 购买者
	float money;//此彩票中奖金额
}Buy;
typedef struct buylink{
	Buy data;
	struct buylink* next;
}Buylink;
/*****发行彩票结构体单元声明****/
typedef struct publish{
	char issue[80];//期号
	float price;//单注价格
	int num[3];//中奖号码
	char state[20];//开奖状态
	int sell_count;//卖出总数
	float total_money;//奖池金额
}Pub;
typedef struct publink{
	Pub data;
	struct publink* next;
}Publink;


void enter_wait(void);//等待回车
int getch();
void getPassword(char *pcPWD);//密码接收
void getname(char *pcPWD);//用户名接收

/********************用户功能函数声明*********************/
void user_regist(Userlink* userlink);//用户注册
Userlink* login_user(Userlink* userlink);//用户登录
void my_message(Userlink* pos);//查看个人信息
void change_password(Userlink* userlink,Userlink* pos);//修改密码
void change_name(Userlink* userlink, Userlink* pos);//修改用户名
void user_recharge(Userlink* userlink, Userlink* pos);//账户充值
void buy_lottery(Userlink* pos, Userlink* userlink, Publink* publink, Buylink* buylink);//购买彩票
void find_my_history(Userlink* pos,Buylink* buylink);//查询个人历史记录
void lock_account(Userlink* pos);//账户注销

/********************管理员功能函数声明*********************/
int login_admin(void);//管理员登录函数
void find_one_user(Userlink* userlink);//查看单个用户信息
void print_all_user(Userlink* userlink);//输出用户信息
void money_interval(Userlink* userlink);//查看金额区间内外用户
void sort_userlink(Userlink* userlink, int len);//排序
void pub_lottery(Publink* publink);//发行彩票
void refind_account(Userlink* userlink);//用户找回
void locked_userlink(Userlink* userlink);//查看注销账户


/********************公正员功能函数声明*********************/
int login_notary(void);//公正员登录
void check_lottery(Publink* publink, Buylink* buylink);//查询彩票信息
void run_lottery(Userlink* userlink,Publink* publink, Buylink* buylink);//开奖
void create_lucky_num(int* p_lucky_num);//用于产生中奖号码
void match_num(Userlink* userlink,Publink* publink, Buylink* buylink, int* p_lucky_num);//号码匹配与奖金发放

/********************用户链表模型函数声明***********************/
Userlink* user_null(Userlink* userlink);//用户链表头节点判断
void userlink_load(Userlink* userlink);//用户链表加载函数
void userlink_save(Userlink* userlink);//用户链表保存函数
void userlink_free(Userlink* userlink);//释放
void userlink_insert_after(Userlink* userlink, User data);//用户链表后插函数
Userlink* userlink_create_new_node(Userlink* userlink,User data);//用户链表节点创建函数
Userlink* userlink_select_node(Userlink* userlink, char name[]);//用户链表姓名查询当前节点
Userlink* userlink_select_front_node(Userlink* userlink, char name[]);//用户链表姓名查询前一个节点


/********************购买彩票链表模型函数声明********************/
Buylink* buy_null(Buylink* buylink);//购买彩票链表头节点判断
void buylink_load(Buylink* buylink);//购买彩票链表加载函数
void buylink_save(Buylink* buylink);//购买彩票链表保存函数
void buylink_free(Buylink* buylink);//释放
void buylink_insert_after(Buylink* buylink, Buy data);//购买彩票链表后插函数
Buylink* buylink_create_new_node(Buylink* buylink,Buy data);//购买彩票链表节点创建函数
Buylink* buylink_select_node(Buylink* buylink, int id);//购买彩票链表ID查询当前节点
Buylink* buylink_select_front_node(Buylink* buylink, int id);//购买彩票链表ID查询前一个节点


/********************发行彩票链表模型函数声明**********************/
Publink* pub_null(Publink* publink);//发行彩票链表头节点判断
void publink_load(Publink* publink);//发行彩票链表加载函数
void publink_save(Publink* publink);//发行彩票链表保存函数
void publink_free(Publink* publink);//释放
void publink_insert_after(Publink* publink, Pub data);//发行彩票链表后插函数
Publink* publink_create_new_node(Publink* publink,Pub data);//发行彩票链表节点创建函数
Publink* publink_select_node(Publink* publink, char issue[]);//发行彩票链表期号查询当前节点
Publink* publink_select_front_node(Publink* publink, char issue[]);//发行彩票链表期号查询前一个节点



#endif
