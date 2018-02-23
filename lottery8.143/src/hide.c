#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <termios.h>
#include "lottery_model.h"

//int getch();
//void getPassword(char *pcPWD);

/*int main()
{
	printf("请输入密码：");
	char temp[20] = "";
	getPassword(temp);
	printf("\n");	
	printf("%s\n",temp);	
	return 0;
}*/


/*****************************************
 * 功能：设置终端为不回显不缓冲，并获取按键的键值
 * 返回值：按键的键值int型
 * 参数：无参数
 ****************************************/
int getch()
{
        struct termios tm, tm_old;
        int fd = STDIN_FILENO, c;
        if(tcgetattr(fd, &tm) < 0)	//获取终端属性
        {
            return -1;
        }
        tm_old = tm;
        cfmakeraw(&tm);	//就是将终端设置为原始模式，该模式下所有的输入数据以字节为单位被处理。
        				//在原始模式下，终端是不可回显的，而且所有特定的终端输入/输出模式不可用。
        if(tcsetattr(fd, TCSANOW, &tm) < 0)	//不等数据传输完毕就立即改变属性   成功返回0   失败-1
        {
            return -1;
        }
        c = fgetc(stdin);//
        if(tcsetattr(fd, TCSANOW, &tm_old) < 0)
        {
            return -1;
        }
        return c;
}
/*****************************************
 * 功能：调用getch获取键值保存到pcPWD中并单个回显*
 * 		可以分别backspace和回车
 * 		用于获取密码
 * 返回值:无返回值
 * 参数：字符数组指针pcPWD
 ****************************************/

void getPassword(char *pcPWD)
{
	int ch=0;
	int i=0;
	for(i=0;i<20;)
	{
		ch=getch();
		if(ch==-1)
		{
			continue;
		}
		if((ch == 127 || ch == 8) && i>0)
		{
			putchar('\b');
			putchar(' ');
			putchar('\b');
			i--;
		}
		else if(ch==10 || ch == 13)
		{
			pcPWD[i]=0;
			putchar('\n');
			return;
		}
		else if(i==0&&(ch==127 ||ch == 8))
		{
			printf("\a");
		}
		else if(i<19)
		{
			pcPWD[i]=(char)ch;
			putchar('*');
			i++;
		}
		else
		{
			printf("\a");
		}
	}
}
void getname(char *pcPWD)
{
	int ch=0;
	int i=0;
	for(i=0;i<20;)
	{
		ch=getch();
		if(ch==-1)
		{
			continue;
		}
		if((ch == 127 || ch == 8) && i>0)
		{
			putchar('\b');
			putchar(' ');
			putchar('\b');
			i--;
		}
		else if(ch==10 || ch == 13)
		{
			pcPWD[i]=0;
			putchar('\n');
			return;
		}
		else if(i==0&&(ch==127 ||ch == 8))
		{
			printf("\a");
		}
		else if(i<19)
		{
			pcPWD[i]=(char)ch;
			putchar(pcPWD[i]);
			i++;
		}
		else
		{
			printf("\a");
		}
	}
}
