#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SPA 0//棋盘空位
#define MAN 1//玩家落子位
#define COM 2//电脑落子位
#define ORDEX 15//棋盘最大列数
typedef struct point{
	int flag;
	int x;
	int y;
}Point;//棋子结构体

int chessboard[ORDEX][ORDEX];//以二维数组形式构建棋盘

void draw(void);//画棋盘

int main(void)
{
	return 0;
}




void draw(void)
{
	int i = 0, j = 0;
	char p[15][15][4];
}
