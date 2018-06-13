#pragma once
#include "Global.h"
class CGameLogic
{
public:
	CGameLogic();
	~CGameLogic();
protected:
	int m_aMap[GAME_ROW][GAME_COL];//游戏地图数组
	PICELEM m_aRemove[GAME_ROW*GAME_COL];
	int m_nRemoveNum;

public:
	void BuildMap();//生成游戏地图数据
	int GetPicNum(int nRow, int nCol);//根据行列获得图片编号
	int NewPicNum();//获取随机编号
	PICELEM GetPicElem(int nRow, int nCol);
	// //判断图片是否相邻
	bool IsNeighbour(PICELEM picElem1,PICELEM picElem2);//判断相邻
	void ExchangeMap(PICELEM &picElem1, PICELEM &picElem2);//交换操作
	bool IsExchange(PICELEM picElem1, PICELEM picElem2);//判断是否成功交换

	void RecordRemove();//记录当前布局所有可消除的图片元素
	void DeleteRecord();//清空m_aRemove[]数组中的记录
	bool IsMapRemove();//判断当前布局是否有图片元素可消除

	void PicDown();//消子、下移和产生新子

	int GetRemoveNum();//获取当前布局可消子个数
	PICELEM GetRemoveElem(int nIndex);//获得数组m_aRemove[]中索引为nIndex的图片元素
	bool CanExchange();
	int GetTotalScore();
	void SetTotalScore(int score);
	PICELEM m_aTip[2];
protected:
	int RowGroupNum(PICELEM picElem);
	int ColGroupNum(PICELEM picElem);
	bool IsElemRemove(PICELEM picElem);

	bool ExchangeTest(PICELEM picElem1, PICELEM picElem2);

	int m_nTotalScore;
	
};

