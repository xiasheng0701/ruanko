#pragma once

typedef struct PICTIREELEMENT
{
	int nRow;//�к�
	int nCol;//�к�
	int nPicNum;//ͼƬ���
}PICELEM;

#define GAME_ROW 8	//��Ϸ����
#define GAME_COL 8	//��Ϸ����


#define INIT_PIC_NUM -1 //��ʼ���

#define	WIDTH 700 //��Ļ��
#define HEIGHT 500 //��Ļ��

//��Ϸ��ʼ����
#define GAME_X 20
#define GAME_Y 20

#define PIC_WIDTH 50 //ͼƬԪ�ؿ�
#define PIC_HEIGHT 50 //ͼƬԪ�ظ�

#define ELEM_NUM 9 //��ɫ����

#define MOVE_PIXEL 10 //ÿ���ƶ�����Ϊ10

#define ELEM_SCORE 15 //ÿ����ʯ����