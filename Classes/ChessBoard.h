/*
���ܣ���������ʹ��
���ߣ�����Դ
λ�ã�Class/ChessBoard��ɸѡ����
��Ϸ���棺Cocos2d-x 4.0
*/
#pragma once

#include <cocos2d.h>

USING_NS_CC;

#include <string>
using std::string;

class chessBoard : public Ref
{
public:
	void move();
	void arrange();
	void print();
private:
	int size[10][10];
	int palacableRange;
};