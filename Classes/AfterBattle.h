/**********
���ܣ��������г������
���ߣ�����Դ-2053291
λ�ã�Class/Controller��ɸѡ����
�汾��1.0.0
��Ϸ���棺cocos2d-x 4.0

************/
#pragma once

#include<cocos2d.h>
#include"ChessPiece.h"
#include"Player.h"
#include<ChessBoard.h>
#include<vector>
USING_NS_CC;

#include <string>
using std::string;

class AfterBattle :public Ref
{
public:

	virtual bool init();

	CREATE_FUNC(AfterBattle);

    void damage(vector<ChessPiece*> A, vector<ChessPiece*> B,Player a,Player b);//���ڼ����һ����ս���л�ʤ,����ȥ��Ӧ��hp

	bool detect(Player a, Player b);//����Ƿ����������

	void shopping();

	void timing();

	//void arrange() ��������е���chessBoard���ƶ�����
private:
	
};
