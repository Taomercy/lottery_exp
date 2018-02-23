#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	srand(time(0));
	char board[62] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	char idcode[5] = "";
	char lowcode[5] = "";
	char incode[100] = "";
	int num = 0;
	int t = 0;
	int i = 0;
	for(i = 0; i < 4; ++i)
	{
		t = 0;
		if(i % 2 != 0)
		{
			while(t < 100000)
			{
				if(t == 99999)
				{
					num = 52+rand()%10;
				}
				++t;
			}
		}
		else
		{
			while(t < 100000)
			{
				if(t == 99999)
				{
					num = rand()%51;
				}
				++t;
			}
		}
		idcode[i] = board[num];
		lowcode[i] = tolower(board[num]);
	}
	printf("\033[45;37m%s\033[0;m\n\033[5m",idcode);
	printf("请输入验证码：");
	scanf("%s",incode);
	for(i = 0; i < 4; ++i)
	{
		incode[i] = tolower(incode[i]);
	}
	if(0 == strcmp(incode,lowcode))
	{
		printf("success!\n");
	}
	else
	{
		printf("fail!\n");
	}
	return 0;
}
