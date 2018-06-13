#pragma once
#include "Global.h"
class CGameLogic
{
public:
	CGameLogic();
	~CGameLogic();
protected:
	int m_aMap[GAME_ROW][GAME_COL];//��Ϸ��ͼ����
	PICELEM m_aRemove[GAME_ROW*GAME_COL];
	int m_nRemoveNum;

public:
	void BuildMap();//������Ϸ��ͼ����
	int GetPicNum(int nRow, int nCol);//�������л��ͼƬ���
	int NewPicNum();//��ȡ������
	PICELEM GetPicElem(int nRow, int nCol);
	// //�ж�ͼƬ�Ƿ�����
	bool IsNeighbour(PICELEM picElem1,PICELEM picElem2);//�ж�����
	void ExchangeMap(PICELEM &picElem1, PICELEM &picElem2);//��������
	bool IsExchange(PICELEM picElem1, PICELEM picElem2);//�ж��Ƿ�ɹ�����

	void RecordRemove();//��¼��ǰ�������п�������ͼƬԪ��
	void DeleteRecord();//���m_aRemove[]�����еļ�¼
	bool IsMapRemove();//�жϵ�ǰ�����Ƿ���ͼƬԪ�ؿ�����

	void PicDown();//���ӡ����ƺͲ�������

	int GetRemoveNum();//��ȡ��ǰ���ֿ����Ӹ���
	PICELEM GetRemoveElem(int nIndex);//�������m_aRemove[]������ΪnIndex��ͼƬԪ��
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

