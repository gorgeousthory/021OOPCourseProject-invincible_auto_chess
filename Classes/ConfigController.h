/**************************************************
 * ���ܣ������ļ���������ʵ�ֶ�ȡ�ͻ��������ļ�����
 * ���ߣ�VenusHui
 * �汾��1.0.2
 * λ�ã�Classes/controller(ɸѡ��)
 * ��Ϸ���棺Cocos2d-x 4.0
 * ************************************************
 * ˵����
 **************************************************/
#pragma once
#include <string>
#include <map>
using std::string;
using std::map;

#include "cocos2d.h"
USING_NS_CC;

class ConfigController
{
public:
	// ConfigController��Ϊһ������
	static ConfigController* getInstance();

	static void destroyInstance();

	~ConfigController();

	// ���ļ��ж�ȡ�������
	static Value getDataByID(int id);

private:
	static  ConfigController* instance;

	// ��������
	static map<int, Value> dataMap;
};

