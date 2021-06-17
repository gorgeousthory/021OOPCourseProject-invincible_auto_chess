#include "PlayScene.h"

inline cocos2d::Sprite* ourCreate(const string & path)
{
	/*auto texture = Director::getInstance()->getTextureCache();
	auto tmpSprite= Sprite::createWithTexture(texture->getTextureForKey(path));*/

	auto tmpSprite = Sprite::create(path);

	return tmpSprite;
}

Scene* PlayScene::createScene()
{
	return PlayScene::create();
}

bool PlayScene::init()
{
	if (!Scene::init()) // �Ը���init�������ж�
		return false;

	// ��Ҫ�õ��ĵ�������
	auto texture = Director::getInstance()->getTextureCache();
	auto config = ConfigController::getInstance();

	// ��ȡ��Ļ�ϵ������λ
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto buttonPositiony = visibleSize.height / 3;	//	The y position of two buttons

	// ���������¼�������
	auto clickListener = EventListenerTouchOneByOne::create();
	clickListener->setSwallowTouches(true);
	clickListener->onTouchBegan = CC_CALLBACK_2(PlayScene::onTouchBegan, this);
	clickListener->onTouchEnded = CC_CALLBACK_2(PlayScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(clickListener, this);

	// �����ƶ��¼�������
	auto moveListener = EventListenerMouse::create();
	moveListener->onMouseMove = CC_CALLBACK_1(PlayScene::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(moveListener, this);

	// ��ӱ�����
	playLayer = Layer::create();
	playLayer->setPosition(origin);
	playLayer->setContentSize(visibleSize);
	this->addChild(playLayer);

	// ��ӱ���ͼƬ
	auto backGround = Sprite::createWithTexture(texture->getTextureForKey("/res/Background/PlaySceneBackground.png"));
	backGround->setPosition(visibleSize / 2);
	Vec2 originSize = backGround->getContentSize();
	backGround->setScale(visibleSize.height / originSize.y);
	playLayer->addChild(backGround, 1);

	// ����˳���ť
	auto exitButton = LoginScene::createGameButton("Exit!", "/res/UI/ExitNormal.png", "/res/UI/ExitSelected.png", CC_CALLBACK_1(PlayScene::menuExitCallBack, this));
	exitButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	originSize = exitButton->getContentSize();
	exitButton->setScale(10 * ConfigController::getInstance()->getPx()->x / originSize.x);
	exitButton->setPosition(Vec2(70 * ConfigController::getInstance()->getPx()->y, -35 * ConfigController::getInstance()->getPx()->y));
	menu = Menu::create(exitButton, nullptr);

	// ��������
	chessBoardModel = ChessBoard::create();
	createBoard(Vec2(config->getPx()->x * 47.5, config->getPx()->y * 16));

	// ��Ӽ�ʱ��
	auto loadingBarBack = Sprite::create("res/UI/LoginLoadingBarBack.png"); // �������ı���
	originSize = loadingBarBack->getContentSize();
	loadingBarBack->setScale(30 * ConfigController::getInstance()->getPx()->x / originSize.x);
	loadingBarBack->setPosition(200, 600);//������������λ��
	auto loadingBarFront = Sprite::create("res/UI/LoginLoadingBarFront.png"); // ��������ǰ��
	loadingBar = ProgressTimer::create(loadingBarFront);
	loadingBar->setBarChangeRate(Vec2(1, 0));
	loadingBar->setType(ProgressTimer::Type::BAR);// ���ý���������
	loadingBar->setMidpoint(Vec2(0, 1));//�����˶�����
	loadingBar->setPosition(200, 600);//��������λ��
	loadingBar->setScale(30 * ConfigController::getInstance()->getPx()->x / originSize.x);
	loadingBar->setPercentage(0);//���ó�ʼֵΪ0
	playLayer->addChild(loadingBarBack, 3);
	playLayer->addChild(loadingBar, 3);


	// �������
	playerA = Player::create();
	playerA->retain();

	// �����̵�
	shopModel = Shop::create();
	shopModel->retain();
	createShop(Vec2(-45 * config->getPx()->x, -45 * config->getPx()->y));
	for (int i = 0; i < 5; i++)
	{
		menu->addChild(shop.at(i));
	}
	playLayer->addChild(menu, 5);

	timeLabel->setPosition(300, 700);
	playLayer->addChild(timeLabel,6);
	
	this->scheduleUpdate();

	return true;
}

void PlayScene::createBoard(Vec2 position)
{
	auto texture = Director::getInstance()->getTextureCache();
	auto config = ConfigController::getInstance();

	auto sprite = Sprite::createWithTexture(texture->getTextureForKey("/res/Background/BoardPiece.png"));
	sprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	Vec2 originSize = sprite->getContentSize();
	float scale = 6.5 * config->getPx()->x / originSize.x;
	sprite->setScale(scale);
	originSize.x *= scale;
	originSize.y *= scale;

	for (int i = 0; i < ROW_BOARD; i++)
	{
		for (int j = 0; j < COL_BOARD; j++)
		{
			if (i == 0 || i == ROW_BOARD - 1 || j == 0 || j == COL_BOARD - 1)
			{
				chessBoard[i].push_back(Sprite::createWithTexture(texture->getTextureForKey("/res/Background/ReadyZone.png")));
			}
			else
			{
				chessBoard[i].push_back(Sprite::createWithTexture(texture->getTextureForKey("/res/Background/BoardPiece.png")));
			}
			chessBoard[i][j]->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
			chessBoard[i][j]->setScale(scale);
			chessBoard[i][j]->setPosition(Vec2(position.x + originSize.x * j, position.y + originSize.y * i));
			playLayer->addChild(chessBoard[i][j], 2);
		}
	}

}

void PlayScene::createShop(Vec2 position)
{
	// ��������
	auto config = ConfigController::getInstance();
	auto texture = Director::getInstance()->getTextureCache();

	// preparations	���ز���UIǰ�����׼��
	auto shopMore = Sprite::createWithTexture(texture->getTextureForKey("/res/UI/ShoppingMore.png"));
	auto buyExp = LoginScene::createGameButton("", "/res/UI/UpgradeNormal.png", "/res/UI/UpgradeSelected.png", CC_CALLBACK_1(PlayScene::menuBuyExpCallBack, this));
	auto freshShop = LoginScene::createGameButton("", "/res/UI/RefreshNormal.png", "/res/UI/RefreshSelected.png", CC_CALLBACK_1(PlayScene::menuFreshShopCallBack, this));
	const Vec2 originSize = shopMore->getContentSize();
	const float scale = 16.9 * config->getPx()->x / originSize.x;	//obtain the reasonable sacle	��ȡ�������ű���
	const Vec2 tmpVec2 = Vec2(position.x + 80 * config->getPx()->x, position.y + 45 * config->getPx()->y);	//obtain the reasonable positon	��ȡ����λ��
	const float singleX = shopMore->getContentSize().width * 0.01 * scale, singleY = shopMore->getContentSize().height * 0.01 * scale;	//obtain reasonable lenth	��ȡ���۵�λ���ȣ�����������
	const float x1 = -5.560 * singleX, y1 = 4.561 * singleY, //x1,y1 refer to the position compared to the bgcard	x1��y1��Ӧ��ť��Ա�������λ�ã���Ĭ�ϴ��ڴ�Сʱ��ʵ��ֵӦ�ӽ�-8��8
				dy = 38.773 * singleY;						//dy refers to the height difference between two buttons	dy��Ӧ���ſ�Ƭ�ĸ߶Ȳ��Ĭ�ϴ��ڴ�Сʱ��ʵ��ֵӦ�ӽ�68

	//adjust the bgcard the two buttons(upgrade and fresh)	��������ͼƬ�����˵��������ˢ�£��������λ��֮�������ͬ��
	//adjust the scale	������С
	shopMore->setScale(scale);
	buyExp->setScale(scale);
	freshShop->setScale(scale);
	//adjust the AnchorPoint	����ê��
	shopMore->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	buyExp->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	freshShop->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	//adjust the Position	������Դ�С
	shopMore->setPosition(tmpVec2);
	buyExp->setPosition(tmpVec2 + Vec2(x1, y1 + dy * 1) + Vec2(- 80 * config->getPx()->x, -45 * config->getPx()->y));
	freshShop->setPosition(tmpVec2 + Vec2(x1, y1 + dy * 0) + Vec2(-80 * config->getPx()->x, -45 * config->getPx()->y));
	//add the parent node	��Ӹ��ڵ�
	playLayer->addChild(shopMore, 5);
	menu->addChild(buyExp);
	menu->addChild(freshShop);

	// ���Ӽ�װ����Ƭ
	auto pieceCard1 = PlayScene::createPieceCard(shopModel->getPieceList()->at(0)->getPieceName(), shopModel->getPieceList()->at(0)->getPicPath(), position, CC_CALLBACK_1(PlayScene::menuPieceCardCallBack1, this));
	auto pieceCard2 = PlayScene::createPieceCard(shopModel->getPieceList()->at(1)->getPieceName(), shopModel->getPieceList()->at(1)->getPicPath(), Vec2(position.x + 1 * 22 * config->getPx()->x, position.y), CC_CALLBACK_1(PlayScene::menuPieceCardCallBack2, this));
	auto pieceCard3 = PlayScene::createPieceCard(shopModel->getPieceList()->at(2)->getPieceName(), shopModel->getPieceList()->at(2)->getPicPath(), Vec2(position.x + 2 * 22 * config->getPx()->x, position.y), CC_CALLBACK_1(PlayScene::menuPieceCardCallBack3, this));
	auto pieceCard4 = PlayScene::createPieceCard(shopModel->getPieceList()->at(3)->getPieceName(), shopModel->getPieceList()->at(3)->getPicPath(), Vec2(position.x + 3 * 22 * config->getPx()->x, position.y), CC_CALLBACK_1(PlayScene::menuPieceCardCallBack4, this));
	auto pieceCard5 = PlayScene::createPieceCard(shopModel->getPieceList()->at(0)->getPieceName(), shopModel->getPieceList()->at(0)->getPicPath(), Vec2(position.x + 4 * 22 * config->getPx()->x, position.y), CC_CALLBACK_1(PlayScene::menuPieceCardCallBack5, this));
	shop.push_back(pieceCard1);
	shop.push_back(pieceCard2);
	shop.push_back(pieceCard3);
	shop.push_back(pieceCard4);
	shop.push_back(pieceCard5);
}

/*���ض�����ǵ�ͼ��,�����������ǵĸ������������еĵ�һ��Ϊ���ڵ�*/
Vector<Sprite*> levelStars(const string& value)
{
	Vector<Sprite*> stars;	//the vector contains the stars;
	int num = 0;
	Vec2 tmp = {};
	for (int i = 0; i < Value(value).asInt(); i++)
	{
		stars.pushBack(Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("/res/Icons/Star.png")));	//the star icon	
		num = stars.size() - 1;
		stars.at(num)->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
		tmp.x += stars.at(0)->getContentSize().width;
		if (0 != num)
		{
			stars.at(num)->setPosition(tmp);
			stars.at(0)->addChild(stars.at(num));
		}
	}
	return stars;
}
MenuItemSprite* PlayScene::createPieceCard(string pieceName, string piecePicPath, Vec2 position, const ccMenuCallback& callback)
{
	auto texture = Director::getInstance()->getTextureCache();
	auto config = ConfigController::getInstance();

	// ������Ƭ����
	auto cardBack = ourCreate(("/res/UI/ShoppingCard.png"));

	// ����һ������˵���
	auto item = MenuItemSprite::create(cardBack, cardBack, callback);

	//fetch the pic and the value stored in the data file "PiecesData.csv"
	CsvParser csv;
	csv.parseWithFile("Data/PiecesData.csv");
	auto rowPosition = csv.findRowOfItem(pieceName);
	auto sprite = ourCreate((piecePicPath));
	auto Healthicon = ourCreate(("/res/Icons/Health.png"));	//the Health icon��������
	auto Attackicon = ourCreate(("/res/Icons/Attack.png"));	//the Attack icon(����)
	auto Armoricon = ourCreate(("/res/Icons/Armor.png"));		//the Armor icon(����)
	auto Name = Label::createWithTTF(csv[rowPosition][D_CH_NAME], "/fonts/Marker Felt.ttf", 150);	//the name of book ��������


	//adjust the comparing position of the icons and values ������Ӧͼ�����ֵ�ڿ�Ƭ�е����λ��
	Vec2 originSize = item->getContentSize();
	sprite->setScale(0.5);
	sprite->setPosition(Vec2(450, 800));
	item->addChild(sprite);

	Name->setPosition(Vec2(450,100));
	Name->setColor(Color3B::BLACK);
	item->addChild(Name);

	const int
		x1 = 1150, y1 = 50,		//the stars position compared to the feature icon	�������������ͼ���λ��
		x2 = 1200, y2 = 700, dy = 400;	//the middle fearture position compared to the card, the height difference �м������������ڿ�Ƭ��λ�ã���������֮��ĸ߶Ȳ�
	const float s1 = 0.8, s2 = 0.4;	//the stars scale, the feature scale	�������ű��������������ű���
	/*Health feature ��������*/
	auto Healthvalue = levelStars(csv[rowPosition][D_HP_LEVEL]).at(0);
	Healthvalue->setPosition(Vec2(x1, y1));
	Healthvalue->setScale(s1);
	Healthicon->addChild(Healthvalue);
	Healthicon->setScale(s2);
	Healthicon->setPosition(Vec2(x2, y2 + dy * 1));
	item->addChild(Healthicon);
	/*Attack feature ��������*/
	auto Attackvalue = levelStars(csv[rowPosition][D_ATK_LEVEL]).at(0);
	Attackvalue->setPosition(Vec2(x1, y1));
	Attackvalue->setScale(s1);
	Attackicon->addChild(Attackvalue);
	Attackicon->setScale(s2);
	Attackicon->setPosition(Vec2(x2, y2 + dy * 0));
	item->addChild(Attackicon);
	/*Armor feature ��������*/
	auto Armorvalue = levelStars(csv[rowPosition][D_DFC_LEVEL]).at(0);
	Armorvalue->setPosition(Vec2(x1, y1));
	Armorvalue->setScale(s1);
	Armoricon->addChild(Armorvalue);
	Armoricon->setScale(s2);
	Armoricon->setPosition(Vec2(x2, y2 - dy * 1));
	item->addChild(Armoricon);

	item->setScale(22 * ConfigController::getInstance()->getPx()->x / originSize.x);//adjust the scale ������С
	item->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	item->setPosition(position);

	return item;
}

PieceCoordinate PlayScene::coordingrevert(Vec2 realPosition)
{
	auto config = ConfigController::getInstance();
	realPosition.x -= config->getPx()->x * 47.5;
	realPosition.y -= config->getPx()->y * 16;

	PieceCoordinate logPosition;
	float perLength = 6.5 * config->getPx()->x;
	logPosition.setX(static_cast<int>(realPosition.x) % static_cast<int>(perLength));
	logPosition.setY(static_cast<int>(realPosition.y) % static_cast<int>(perLength));

	return logPosition;
}

void PlayScene::update(float dt)
{
	string temp = "Time:";
	float damage = 0;
	if (timeRemaining > 0.5f) {
		timeRemaining -= dt;
		damage = 61.0 - timeRemaining;

		temp += (to_string(static_cast<int>(timeRemaining)));
		timeLabel->setString(temp);
		loadingBar->setPercentage((damage / 61.0) * 100);
	}
	//else {//ʱ�䵽��

	//}
}

void PlayScene::menuExitCallBack(Ref* sender)
{
	Director::getInstance()->end();
}

void PlayScene::menuPieceCardCallBack1(Ref* sender)
{
	// ��ȡ����ǰ����������ӿ�Ƭ
	const int NUMBER = 0;
	if (shopQualification[0]==0) {
		CCLOG("emptyShop");
	}
	else {
		buyCard(NUMBER);
		shopQualification[0] = 0;
		shop.at(NUMBER)->setEnabled(false);
	}
}

void PlayScene::menuPieceCardCallBack2(Ref* sender)
{
	const unsigned int NUMBER = 1;
	if (shopQualification[1] == 0) {
		CCLOG("emptyShop");
	}
	else {//����
		buyCard(NUMBER);
		shopQualification[1] = 0;
		shop.at(NUMBER)->setEnabled(false);
	}
}

void PlayScene::menuPieceCardCallBack3(Ref* sender)
{
	const unsigned int NUMBER = 2;
	if (shopQualification[2] == 0) {
		CCLOG("emptyShop");
	}
	else {
		buyCard(NUMBER);
		shopQualification[2] = 0;
		shop.at(NUMBER)->setEnabled(false);
	}
}

void PlayScene::menuPieceCardCallBack4(Ref* sender)
{
	const unsigned int NUMBER = 3;
	if (shopQualification[3] == 0) {
		CCLOG("emptyShop");
	}
	else {
		buyCard(NUMBER);
		shopQualification[3] = 0;
		shop.at(NUMBER)->setEnabled(false);
	}
}

//װ���� 
void PlayScene::menuPieceCardCallBack5(Ref* sender)
{
	const unsigned int NUMBER = 4;
	buyCard(NUMBER);
	shop.at(NUMBER)->removeFromParent();
}

void PlayScene::buyCard(const unsigned int num)
{
	ChessPiece* piece = shopModel->getPieceList()->at(num);

	//����
	if (shopModel->qualification(playerA->getMoney(),playerA->getMaxPieceStorage(),playerA->getOwnPieceNum(),piece->getPiecePerCost()))
	{
		playerA->piecePossesion[playerA->getOwnPieceNum()] = piece;
		playerA->retain();
		this->addChild(piece->createChessPiece("a", "/res/Books/AdvancedMathematics.png", Vec2(200, 300), 0));
		CCLOG("BUY");
	}
	else {
		CCLOG("UNAFFORDABLE");
	}
}

void PlayScene::menuFreshShopCallBack(Ref* sender)
{
	auto config = ConfigController::getInstance();

	shopModel->refresh();
	Vec2 position = Vec2(-config->getPx()->x * 45, -config->getPx()->y * 45);
	for (unsigned int i = 0; i < shop.size(); i++)
	{
		shop.at(i)->removeFromParent();
		shop.at(i)->release();
	}
	for (int i = 0; i < 5;i++) {
		shopQualification[i] = 1;
	}
	shop.clear();
	auto pieceCard1 = PlayScene::createPieceCard(shopModel->getPieceList()->at(0)->getPieceName(), shopModel->getPieceList()->at(0)->getPicPath(), position, CC_CALLBACK_1(PlayScene::menuPieceCardCallBack1, this));
	auto pieceCard2 = PlayScene::createPieceCard(shopModel->getPieceList()->at(1)->getPieceName(), shopModel->getPieceList()->at(1)->getPicPath(), Vec2(position.x + 1 * 22 * config->getPx()->x, position.y), CC_CALLBACK_1(PlayScene::menuPieceCardCallBack2, this));
	auto pieceCard3 = PlayScene::createPieceCard(shopModel->getPieceList()->at(2)->getPieceName(), shopModel->getPieceList()->at(2)->getPicPath(), Vec2(position.x + 2 * 22 * config->getPx()->x, position.y), CC_CALLBACK_1(PlayScene::menuPieceCardCallBack3, this));
	auto pieceCard4 = PlayScene::createPieceCard(shopModel->getPieceList()->at(3)->getPieceName(), shopModel->getPieceList()->at(3)->getPicPath(), Vec2(position.x + 3 * 22 * config->getPx()->x, position.y), CC_CALLBACK_1(PlayScene::menuPieceCardCallBack4, this));
	auto pieceCard5 = PlayScene::createPieceCard(shopModel->getPieceList()->at(0)->getPieceName(), shopModel->getPieceList()->at(0)->getPicPath(), Vec2(position.x + 4 * 22 * config->getPx()->x, position.y), CC_CALLBACK_1(PlayScene::menuPieceCardCallBack5, this));
	shop.push_back(pieceCard1);
	shop.push_back(pieceCard2);
	shop.push_back(pieceCard3);
	shop.push_back(pieceCard4);
	shop.push_back(pieceCard5);
	for (unsigned int i = 0; i < shop.size(); i++)
	{
		menu->addChild(shop.at(i));
	}
}

void PlayScene::menuBuyExpCallBack(Ref* sender)
{

}

int PlayScene::onTouchBegan(Touch* touch, Event* event)
{
	Vec2 position = touch->getLocation();
	if (position.x > chessBoard[1][1]->getPositionX() && position.x < chessBoard[1][9]->getPositionX() && 
		position.y > chessBoard[1][1]->getPositionY() && position.y < chessBoard[5][1]->getPositionY()) // ���������ս����
	{
		CCLOG("WAR");
		return IN_WAR_ZONE;
	}
	else if (position.x > chessBoard[0][1]->getPosition().x && position.x < chessBoard[0][9]->getPosition().x &&
			 position.y > chessBoard[0][1]->getPosition().y && position.y < chessBoard[1][1]->getPosition().y)
	{
		CCLOG("READY");
		return IN_READY_ZONE;
	}
	else
	{

		return NOT_IN_BOARD;
	}
}

void PlayScene::onTouchEnded(Touch* touch, Event* event)
{
	Vec2 position = touch->getLocation();
	PieceCoordinate logPosition = coordingrevert(position);

	// int clickType = PlayScene::onTouchBegan(touch, event);
	/*switch (clickType)
	{
		case IN_WAR_ZONE:
			if (board->getPlayerA_WarZone_Pieces()[logPosition->getX()][logPosition->getY()] != nullptr)
			{
				chessBoard[logPosition->getY() + 1][logPosition->getX()]->setOpacity(50);
			}
			break;

		case IN_READY_ZONE:
			if (board->getPlayerA_PreZone_Pieces()->at(logPosition->getX()) != nullptr)
			{
				chessBoard[0][logPosition->getX()]->setOpacity(50);
			}
			break;

		default:
			break;
	}*/

}

void PlayScene::onMouseMove(Event* event)
{
	EventMouse* e = (EventMouse*)event;
}
