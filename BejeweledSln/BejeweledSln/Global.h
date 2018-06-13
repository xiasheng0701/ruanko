#pragma once

typedef struct PICTIREELEMENT
{
	int nRow;//行号
	int nCol;//列号
	int nPicNum;//图片编号
}PICELEM;

#define GAME_ROW 8	//游戏行数
#define GAME_COL 8	//游戏列数


#define INIT_PIC_NUM -1 //初始编号

#define	WIDTH 700 //屏幕宽
#define HEIGHT 500 //屏幕高

//游戏起始坐标
#define GAME_X 20
#define GAME_Y 20

#define PIC_WIDTH 50 //图片元素宽
#define PIC_HEIGHT 50 //图片元素高

#define ELEM_NUM 9 //花色数量

#define MOVE_PIXEL 10 //每次移动像素为10

#define ELEM_SCORE 15 //每个宝石分数