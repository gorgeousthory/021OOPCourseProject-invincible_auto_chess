/********************************************
 * ���ܣ�������(��������)
 * ���ߣ�����Դ
 * �汾��1.0.0
 * λ�ã�Classes/model(ɸѡ��)
 * ��Ϸ���棺Cocos2d-x 4.0
 * ******************************************
 * ˵�������ڴ��湺������ӣ�����ɾ��������Ĺ���
 ********************************************/
#pragma once
#ifndef _STORAGE_
#define _STORAGE

#include<cocos2d.h>
USING_NS_CC;

#include"ChessPiece.h"

#include<vector>
using namespace std;

class Storage :public Ref
{
public:

	virtual bool init();

	void tankStore(tank obj);
	void tankRemove(tank* ptr);

	void mageStore(mage obj);
	void mageRemove(mage* ptr);

	void shooterStore(shooter obj);
	void shooterRemove(shooter* ptr);

	void stalkerStore(stalker obj);
	void stalkerRemove(stalker* ptr);

	void therapistStore(therapist obj);
	void therapistRemove(therapist* ptr);

private:

	vector<tank> tankStorage;

	vector<mage> mageStorage;

	vector<shooter> shooterStorage;

	vector <stalker> stalkerStorage;

	vector<therapist> therapistStorage;
};

#endif