#include"clock.h"

Layer* Clock::createLayer()
{
	return Clock::create();
}

bool Clock::init()
{
	if (!Layer::init()) {
		return false;
	}

	//��ʼ���ɹ�

	// ��ȡ��Ļ�ϵĸ������
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto clock = Layer::create();
	clock->setPosition(origin);
	clock->setContentSize(visibleSize);
	this->addChild(clock);

	//�˺��Ӧ��Ա���ڴ˴�������Ӧ�Ŀ��ӻ�ʵ�֣����������

	this->addChild(timeLabel);
	this->scheduleUpdate();

	return true;
}

void Clock::update(float dt)
{
	string temp = "Time:";
	if (remainingTime > 0.5f) {
		remainingTime -= dt;
		temp += to_string(static_cast<int>(remainingTime));
		timeLabel->setString(temp);
	}
	/*else {
	��һ������Ҫдǿ��ת���Ĺ���
	}*/
}
