#include "cocos2d.h"
#include "LoginScene.h"
USING_NS_CC;

#include "ui/CocosGUI.h" 
using namespace ui;

Scene* LoginScene::createScene()
{
	return LoginScene::create();
}

bool LoginScene::init()
{
	if (!Scene::init()) // �Ը���init�������ж�
		return false;
	
	// ��ȡ��Ļ�ϵ������λ
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	
	// ��Ӱ�ɫ������
	auto backLayer = LayerColor::create(Color4B::WHITE);
	backLayer->setPosition(origin);
	backLayer->setContentSize(visibleSize);
	this->addChild(backLayer);

	auto startButton = Button::create("CloseNormal.png", "CloseSelected.png", "CloseSelected.png");
	startButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	startButton->setPosition(visibleSize / 2);
	this->addChild(startButton);
	startButton->addTouchEventListener(
        [&](Ref* sender, Widget::TouchEventType type) {
            if (type == Widget::TouchEventType::ENDED)
            {
				Director::getInstance()->end();
            }
        }
    );

	return true;
}
