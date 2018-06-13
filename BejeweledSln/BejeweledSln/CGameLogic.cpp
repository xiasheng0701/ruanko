#include "stdafx.h"
#include "CGameLogic.h"
#include "CGameDlg.h"
#include<stdlib.h>
#include<time.h>


CGameLogic::CGameLogic()
{
	for (int i = 0; i < GAME_ROW; i++)
	{
		for (int j = 0; j < GAME_COL; j++)
		{
			m_aMap[i][j] = INIT_PIC_NUM;
		}
	}

	srand((unsigned)time(NULL));
	memset(m_aRemove, NULL, sizeof(PICELEM)*GAME_ROW*GAME_COL);
	m_nRemoveNum = 0;
	m_nTotalScore = 0;
}


CGameLogic::~CGameLogic()
{
}


void CGameLogic::BuildMap()
{
	for (int i = 0; i < GAME_ROW; i++)
	{
		for (int j = 0; j < GAME_COL; j++)
		{
			m_aMap[i][j] = NewPicNum();
		}
	}
	while (IsMapRemove())
	{
		RecordRemove();
		PicDown();
		DeleteRecord();
	}
	if (!CanExchange())
		BuildMap();

	// TODO: 在此处添加实现代码.
}

int CGameLogic::GetPicNum(int nRow, int nCol)
{
	return m_aMap[nRow][nCol];
}

int CGameLogic::NewPicNum()
{
	return rand() % ELEM_NUM;
}

PICELEM CGameLogic::GetPicElem(int nRow, int nCol)
{
	PICELEM picElem;
	picElem.nRow = nRow;
	picElem.nCol = nCol;
	picElem.nPicNum = GetPicNum(nRow, nCol);
	return picElem;
}


// //判断图片是否相邻
bool CGameLogic::IsNeighbour(PICELEM picElem1, PICELEM picElem2)
{
	//行相等
	if (picElem1.nRow == picElem2.nRow && abs(picElem1.nCol - picElem2.nCol) == 1)
		return true;
	if (picElem1.nCol == picElem2.nCol && abs(picElem1.nRow - picElem2.nRow) == 1)
		return true;
	// TODO: 在此处添加实现代码.
	return false;
}

void CGameLogic::ExchangeMap(PICELEM &picElem1, PICELEM &picElem2)
{
	//将两图片元素的结构体图片编号互换
	int nTemp = picElem1.nPicNum;
	picElem1.nPicNum = picElem2.nPicNum;
	picElem2.nPicNum = nTemp;
	//将数组中的图片编号更新
	m_aMap[picElem1.nRow][picElem1.nCol] = picElem1.nPicNum;
	m_aMap[picElem2.nRow][picElem2.nCol] = picElem2.nPicNum;
}

int CGameLogic::RowGroupNum(PICELEM picElem)
{
	int nFlag = 1;
	if (picElem.nCol > 0 && picElem.nPicNum==GetPicNum(picElem.nRow, picElem.nCol-1))
	{
		nFlag++;
		if (picElem.nCol > 1 && picElem.nPicNum == GetPicNum(picElem.nRow, picElem.nCol - 2))
			nFlag++;
	}
	if (picElem.nCol < GAME_COL- 1&& picElem.nPicNum == GetPicNum(picElem.nRow, picElem.nCol + 1))
	{
		nFlag++;
		if (picElem.nCol < GAME_COL - 2 && picElem.nPicNum == GetPicNum(picElem.nRow, picElem.nCol + 2))
			nFlag++;
	}
	return nFlag;
}

int CGameLogic::ColGroupNum(PICELEM picElem)
{
	int nFlag = 1;
	if (picElem.nRow > 0 && picElem.nPicNum == GetPicNum(picElem.nRow - 1, picElem.nCol))
	{
		nFlag++;
		if (picElem.nRow > 1 && picElem.nPicNum == GetPicNum(picElem.nRow - 2, picElem.nCol))
			nFlag++;
	}
	if (picElem.nRow < GAME_ROW - 1 && picElem.nPicNum == GetPicNum(picElem.nRow + 1, picElem.nCol))
	{
		nFlag++;
		if (picElem.nRow < GAME_ROW - 2 && picElem.nPicNum == GetPicNum(picElem.nRow + 2, picElem.nCol))
			nFlag++;
	}
	return nFlag;
}

bool CGameLogic::IsElemRemove(PICELEM picElem)
{
	int nRowNum = RowGroupNum(picElem);
	int nColNum = ColGroupNum(picElem);

	if (nRowNum >= 3 || nColNum >= 3)
		return true;
	return false;
}

bool CGameLogic::ExchangeTest(PICELEM picElem1, PICELEM picElem2)
{
	bool nFlag = false;
	ExchangeMap(picElem1, picElem2);

	if (IsExchange(picElem1,picElem2))
	{
		nFlag = true;
	}
	ExchangeMap(picElem1, picElem2);
	return nFlag;
}

void CGameLogic::RecordRemove()
{
	PICELEM picElem;
	for (int i = 0; i < GAME_ROW; i++)
	{
		for (int j = 0; j < GAME_COL; j++)
		{
			picElem = GetPicElem(i, j);
			if (IsElemRemove(picElem))
			{
				m_aRemove[m_nRemoveNum] = picElem;
				m_nRemoveNum++;
			}
		}
	}
}

void CGameLogic::DeleteRecord()
{
	PICELEM picElem;
	picElem.nPicNum = INIT_PIC_NUM;
	for (int i = 0; i < m_nRemoveNum; i++)
	{
		m_aRemove[i] = picElem;
	}
	m_nRemoveNum = 0;
}

bool CGameLogic::IsMapRemove()
{
	PICELEM picElem;
	for (int i = 0; i < GAME_ROW; i++)
	{
		for (int j = 0; j < GAME_COL; j++)
		{
			picElem = GetPicElem(i, j);
			if (IsElemRemove(picElem))
			{
				return true;
			}
		}
	}
	return false;
}

void CGameLogic::PicDown()
{
	int nTi = 0;
	int nTj = 0;
	for (int i = 0; i < m_nRemoveNum; i++)
	{
		nTi = m_aRemove[i].nRow;
		nTj = m_aRemove[i].nCol;

		while (nTi > 0)
		{
			m_aMap[nTi][nTj] = m_aMap[nTi - 1][nTj];
			nTi--;
		}
		m_aMap[nTi][nTj] = NewPicNum();
	}
}

int CGameLogic::GetRemoveNum()
{
	return m_nRemoveNum;
}

PICELEM CGameLogic::GetRemoveElem(int nIndex)
{
	return m_aRemove[nIndex];
}

bool CGameLogic::CanExchange()
{
	PICELEM picElem1;
	PICELEM picElem2;
	for (int i = 0; i < GAME_ROW-1; i++)
	{
		for (int j = 0; j < GAME_COL-1; j++)
		{
			picElem1 = GetPicElem(i, j);
			picElem2 = GetPicElem(i, j + 1);
			if (ExchangeTest(picElem1, picElem2))
			{
				m_aTip[0] = picElem1;
				m_aTip[1] = picElem2;
				return true;
			}
		}
	}
	for (int y = 0; y < GAME_COL-1; y++)
	{
		for (int x = 0; x < GAME_ROW-1; x++)
		{
			picElem1 = GetPicElem(x, y);
			picElem2 = GetPicElem(x+1,y);
			if (ExchangeTest(picElem1, picElem2))
			{
				m_aTip[0] = picElem1;
				m_aTip[1] = picElem2;
				return true;
			}
		}
	}
	return false;
}

int CGameLogic::GetTotalScore()
{
	m_nTotalScore += m_nRemoveNum * ELEM_SCORE;
	return m_nTotalScore;
}

void CGameLogic::SetTotalScore(int score)
{
	m_nTotalScore = score;
}

bool CGameLogic::IsExchange(PICELEM picElem1, PICELEM picElem2)
{
	if (IsElemRemove(picElem1) || IsElemRemove(picElem2))
		return true;
	return false;
}
