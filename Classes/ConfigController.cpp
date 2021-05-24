#include "ConfigController.h"

ConfigController* ConfigController::instance = nullptr;

ConfigController* ConfigController::getInstance()
{
	if (instance == nullptr)
	{
		instance = new ConfigController();
	}
	return instance;
}

void ConfigController::destroyInstance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

ConfigController::~ConfigController()
{
	dataMap.clear();
}

Value ConfigController::getDataByID(int id)
{
	//�������Ϊ�գ�ȥ��ȡ�����ļ�����Ϊ�ղ���Ҫ��ȡ
	if (dataMap.empty())
	{
		//��ȡ�����ļ�
		auto data = FileUtils::getInstance()->getValueMapFromFile("");
		for (auto mapPair : data)
		{
			int key = Value(mapPair.first).asInt();
			Value val = mapPair.second;

			dataMap.insert(std::pair<int,Value>(key, val));
		}
	}

	if (dataMap.empty())
	{
		return Value::Null;
	}

	return dataMap.at(id);
}
