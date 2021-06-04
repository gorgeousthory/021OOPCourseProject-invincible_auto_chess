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

	// ���ӻ����ֿ�ʼ

	// ��ȡ��Ļ�ϵĸ������
	// �Զ���һ�����ص�Ĵ�С���������л��ͣ���������ͳһʹ��
	static const Vec2 px = Vec2(Director::getInstance()->getVisibleSize().width / HORIZONTAL_PIXEL_NUM, Director::getInstance()->getVisibleSize().height / VERTICAL_PIXEL_NUM);







	// ���ӻ����ֽ���

	auto endButton = Button::create("CloseNormal.png", "CloseSelected.png", "CloseSelected.png");
	endButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	endButton->setTitleLabel(Label::createWithTTF("EXIT", "fonts/Marker Felt.ttf", 52));
	endButton->setPosition(Vec2(10 * px.x, 10 * px.y));
	this->addChild(endButton, 1);
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
	resTotal = 9;
	dataPathList.clear();

	// �����ҪԤ���ص���Դ·����ÿ���ļ�����ֻ�����һ�������ļ��������ļ����Զ�ȫ������
	dataPathList.push_back("CloseSelected.png");
	dataPathList.push_back("res/Books/AdvancedMathematics.png");
	dataPathList.push_back("res/Background/BoardPiece.png");
	dataPathList.push_back("res/Icons/Armor.png");

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
	filePath.at(sign.back()) = '\0'; // �����һ��'/'���ض��ַ�����Ϊ�����ļ��еľ���·��

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
	auto label = Label::createWithSystemFont(name, "����Ҧ��", 144);
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