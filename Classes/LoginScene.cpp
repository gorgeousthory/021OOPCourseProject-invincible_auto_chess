#include "LoginScene.h"
Scene* LoginScene::createScene()
{
	return LoginScene::create();
}

// �����ֽڱ���ת��Ϊ���ֽڱ���
wstring string2wstring(string str);

bool LoginScene::init()
{
	if (!Scene::init())
		return false;

	// ************���ӻ����ֿ�ʼ***************

	// ��ȡ��Ļ�ϵĸ������
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	
	// LoginScene������
	auto loginLayer = Layer::create();
	loginLayer->setPosition(origin);
	loginLayer->setContentSize(visibleSize);
	this->addChild(loginLayer);

	// ��������֡����
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("res/Background/LoginSceneAnimation.plist", "res/Background/LoginSceneAnimation.png"); // ����ͼ����Դ
	auto sprite = Sprite::createWithSpriteFrameName("image0.png"); // �Ե�һ֡������������
	sprite->setPosition(visibleSize / 2);
	Vec2 originSize = sprite->getContentSize();
	sprite->setScale(visibleSize.width / originSize.x);
	loginLayer->addChild(sprite, 1);
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 7; i++)
	{
		string str = "image";
		str.push_back('0' + i);
		str += ".png";
		images.pushBack(cache->getSpriteFrameByName(str));
	}
	auto animation = Animation::createWithSpriteFrames(images, 1.0f / images.size());
	auto animate = Animate::create(animation);
	sprite->runAction(RepeatForever::create(animate)); // ִ�ж���

	// �����ϷLOGO
	auto gameLogo = Sprite::create("res/UI/Logo.PNG");
	gameLogo->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	originSize = gameLogo->getContentSize();
	gameLogo->setScale(80 * ConfigController::getInstance()->getPx()->x / originSize.x);
	gameLogo->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 5 * ConfigController::getInstance()->getPx()->y));
	loginLayer->addChild(gameLogo, 2);
	
	// �����Դ���ؽ�����
	auto loadingBarBack = Sprite::create("res/UI/LoginLoadingBarBack.png"); // �������ı���
	originSize = loadingBarBack->getContentSize();
	loadingBarBack->setScale(30 * ConfigController::getInstance()->getPx()->x / originSize.x);
	loadingBarBack->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 37 * ConfigController::getInstance()->getPx()->y);
	loginLayer->addChild(loadingBarBack, 3);
	auto loadingBarFront = Sprite::create("res/UI/LoginLoadingBarFront.png"); // ��������ǰ��

	loadingBar = ProgressTimer::create(loadingBarFront);
	loadingBar->setBarChangeRate(Vec2(1, 0));
	loadingBar->setType(ProgressTimer::Type::BAR);// ���ý���������
	loadingBar->setMidpoint(Vec2(0, 1));//�����˶�����
	loadingBar->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 37 * ConfigController::getInstance()->getPx()->y);
	loadingBar->setScale(30 * ConfigController::getInstance()->getPx()->x / originSize.x);
	loadingBar->setPercentage(0);//���ó�ʼֵΪ0
	loginLayer->addChild(loadingBar, 3);

	// ************���ӻ����ֽ���***************

	auto endButton = Button::create("CloseNormal.png", "CloseSelected.png", "CloseSelected.png");
	endButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	endButton->setTitleLabel(Label::createWithTTF("EXIT", "fonts/Marker Felt.ttf", 52));
	endButton->setPosition(Vec2(10 * ConfigController::getInstance()->getPx()->x, 10 * ConfigController::getInstance()->getPx()->y));
	loginLayer->addChild(endButton, 2);
	endButton->addTouchEventListener(
		[&](Ref* sender, Widget::TouchEventType type) {
			if (type == Widget::TouchEventType::ENDED)
			{
				Director::getInstance()->end();
			}
		}
	);

	// ��ʼ��������ص���Դ������·����
	resCount = 0;
	resTotal = 23;
	dataPathList.clear();

	// �����ҪԤ���ص���Դ·����ÿ���ļ�����ֻ�����һ�������ļ��������ļ����Զ�ȫ������
	dataPathList.push_back("CloseSelected.png");
	dataPathList.push_back("res/Books/AdvancedMathematics.png");
	dataPathList.push_back("res/Background/BoardPiece.png");
	dataPathList.push_back("res/UI/PlayNormal.png");

	// ���м���
	this->loadResources();

	return true;
}

list<string> LoginScene::getFileFromPath(string path)
{
	list<string> files; // �����ļ���

	// �����ļ�����ȡ���ļ��ľ���·����û�ҵ���ֱ�ӻ�ȡ�����ļ��еķ�����ֻ���Ȼ�ȡ����·���ٽ���ת��
	string filePath = FileUtils::getInstance()->fullPathForFilename(path);
	// ���ڵ�filePath�Ǹ��ļ����ڵľ���·�������ڽ���ת��Ϊ�����ļ��е�·���Խ�����ļ���
	vector<unsigned int> sign;
	for (unsigned int i = 0; i < filePath.size(); i++)
	{	
		if (filePath.at(i) == '/')
		{
			sign.push_back(i);
		}
	}
	filePath = filePath.substr(0, sign.back());
	// filePath.at(sign.back()) = '\0'; // �����һ��'/'���ض��ַ�����Ϊ�����ļ��еľ���·��
	sign.clear();

	DIR* dp;
	struct dirent* entry;
	struct stat statbuf;
	dp = opendir(filePath.c_str());

	// ת��Ϊ���ַ�����
	wstring wFilePath = string2wstring(filePath);

	// ���뵽���ļ��е���
	_wchdir(wFilePath.c_str());
	// �������ļ����µ������ļ�����¼
	while ((entry = readdir(dp)) != NULL)
	{
		stat(entry->d_name, &statbuf);
		if (!S_ISREG(statbuf.st_mode))
			continue;
		files.push_back(path + "/" + entry->d_name);
	}

	return files;
}

void LoginScene::loadResources()
{
	CCLOG("start loading"); // ��ʼ����
	while (dataPathList.size() > 0)
	{
		// ������أ������˳��Ӱ��
		list<string> files = getFileFromPath(dataPathList.back());
		while (files.size() > 0)
		{
			// ���ص��ڴ���
			Director::getInstance()->getTextureCache()->addImage(files.back());
			resCount++;
			loadingBar->setPercentage(resCount / resTotal * 100);
			CCLOG("loading %s", files.back().c_str());
			files.pop_back(); // ���ļ��б�������Ѽ�����ϵ��ļ�
		}
		dataPathList.pop_back();
	}
}


MenuItemSprite* LoginScene::createGameButton(string name, string normalPicPath, string pressedPicPath, const ccMenuCallback& callback)
{
	auto normalPic = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(normalPicPath));
	auto pressedPic = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(pressedPicPath));

	// ����һ������˵���
	auto item = MenuItemSprite::create(normalPic, pressedPic, callback);

	//��ť���ֱ�ǩ
	auto label = Label::createWithTTF(name, "fonts/Marker Felt.ttf", 52);
	label->setPosition(item->getContentSize() / 2);
	label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	label->setColor(Color3B::WHITE);
	item->addChild(label);

	return item;
}

void LoginScene::menuStartCallBack(Ref* sender)
{
	auto scene = PlayScene::create();
	Director::getInstance()->replaceScene(scene);
}

// �����ֽڱ���ת��Ϊ���ֽڱ���
wstring string2wstring(string str)
{
	wstring result;

	//��ȡ��������С��������ռ䣬��������С���ַ�����
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
	TCHAR* buffer = new TCHAR[len + 1];

	//���ֽڱ���ת���ɿ��ֽڱ���  
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
	buffer[len] = '\0';//����ַ�����β 

	//ɾ��������������ֵ  
	result.append(buffer);
	delete[] buffer;
	return result;
}