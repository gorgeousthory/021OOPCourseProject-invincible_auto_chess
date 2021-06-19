#include "PlayScene.h"

Scene* PlayScene::createScene()
{
	return PlayScene::create();
}

bool PlayScene::init()
{
	if (!Scene::init()) // �Ը���init�������ж�
		return false;

	mouseLiftPiece = nullptr;

	// ��Ҫ�õ��ĵ�������
	auto texture = Director::getInstance()->getTextureCache();
	auto config = ConfigController::getInstance();

	// ��ȡ��Ļ�ϵ������λ
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto buttonPositiony = visibleSize.height / 3;	//	The y position of two buttons

	// ��ӱ�����
	playLayer = Layer::create();
	playLayer->setPosition(origin);
	playLayer->setContentSize(visibleSize);
	this->addChild(playLayer);

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
	chessBoardModel->retain();
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
	playLayer->addChild(timeLabel, 6);
	
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
				pieceBoard[i].push_back(nullptr);
			}
			else
			{
				chessBoard[i].push_back(Sprite::createWithTexture(texture->getTextureForKey("/res/Background/BoardPiece.png")));
				pieceBoard[i].push_back(nullptr);
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
	auto cardBack = Sprite::createWithTexture(texture->getTextureForKey("/res/UI/ShoppingCard.png"));

	// ����һ������˵���
	auto item = MenuItemSprite::create(cardBack, cardBack, callback);

	//fetch the pic and the value stored in the data file "PiecesData.csv"
	CsvParser csv;
	csv.parseWithFile("Data/PiecesData.csv");
	auto rowPosition = csv.findRowOfItem(pieceName);
	auto sprite = Sprite::createWithTexture(texture->getTextureForKey(piecePicPath));
	auto Healthicon = Sprite::createWithTexture(texture->getTextureForKey("/res/Icons/Health.png"));	//the Health icon��������
	auto Attackicon = Sprite::createWithTexture(texture->getTextureForKey("/res/Icons/Attack.png"));	//the Attack icon(����)
	auto Armoricon = Sprite::createWithTexture(texture->getTextureForKey("/res/Icons/Armor.png"));		//the Armor icon(����)
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

Sprite* PlayScene::createChessPiece(string pieceName, string piecePicPath, Vec2 position, int type)
{
	auto texture = Director::getInstance()->getTextureCache();
	auto config = ConfigController::getInstance();

	CsvParser csv;
	csv.parseWithFile("Data/PiecesData.csv");

	auto piece = Sprite::createWithTexture(texture->getTextureForKey(piecePicPath));
	auto hpBar = Sprite::createWithTexture(texture->getTextureForKey("/res/UI/HpBar.png"));//������
	auto mpBar = Sprite::createWithTexture(texture->getTextureForKey("/res/UI/MpBar.png"));//����
	/*auto hpDecreaseBar = Sprite::createWithTexture(texture->getTextureForKey("/res/UI/MpBar.png"));//����
	auto mpDecreaseBar = Sprite::createWithTexture(texture->getTextureForKey("/res/UI/MpBar.png"));//����

	hpDecreaseBar->setColor(Color3B::BLACK);
	mpDecreaseBar->setColor(Color3B::BLACK);

	ProgressTimer* hp, mp;
	hp = ProgressTimer::create(hpDecreaseBar);*/
	int tag = static_cast<int>(100 + 10 * position.x + position.y);
	piece->setTag(tag);
	piece->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	Vec2 originSize = piece->getContentSize();
	float scale = 5 * config->getPx()->x / originSize.x;
	piece->setScale(scale);
	PieceCoordinate realPosition = coordingRevert(CoordinateType::logical, position);
	piece->setPosition(realPosition.getX(), realPosition.getY());
	if (type == 1) {
		piece->addChild(hpBar);
		piece->addChild(mpBar);
	}
	return piece;
}

PieceCoordinate PlayScene::coordingRevert(CoordinateType originType, Vec2 originPosition)
{
	auto config = ConfigController::getInstance();

	float perLength = 6.5 * config->getPx()->x;
	if (originType == CoordinateType::real)
	{
		originPosition.x -= config->getPx()->x * 47.5;
		originPosition.y -= config->getPx()->y * 16;

		PieceCoordinate logPosition;
		logPosition.setX(static_cast<int>(originPosition.x / perLength));
		logPosition.setY(static_cast<int>(originPosition.y / perLength));
		return logPosition;
	}
	else
	{
		originPosition.x = originPosition.x * perLength + config->getPx()->x * 47.5;
		originPosition.y = originPosition.y * perLength + config->getPx()->y * 16;

		PieceCoordinate realPosition;
		realPosition.setX(static_cast<int>(originPosition.x));
		realPosition.setY(static_cast<int>(originPosition.y));
		return realPosition;
	}
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
	Director::getInstance()->getTextureCache()->removeAllTextures();
	Director::getInstance()->end();
}

void PlayScene::menuPieceCardCallBack1(Ref* sender)
{
	// ��ȡ����ǰ����������ӿ�Ƭ
	const int NUMBER = 0;
	ChessPiece* piece = shopModel->getPieceList()->at(NUMBER);
	//����
	if (shopModel->qualification(playerA->getMoney(), playerA->getMaxPieceStorage(), playerA->getPlayerPiecePossesion()->size(), piece->getPiecePerCost()))
	{
		buyCard(NUMBER, piece);
		shop.at(NUMBER)->setVisible(false);
		shop.at(NUMBER)->setEnabled(false);
	}
}

void PlayScene::menuPieceCardCallBack2(Ref* sender)
{
	const unsigned int NUMBER = 1;
	ChessPiece* piece = shopModel->getPieceList()->at(NUMBER);
	//����
	if (shopModel->qualification(playerA->getMoney(), playerA->getMaxPieceStorage(), playerA->getPlayerPiecePossesion()->size(), piece->getPiecePerCost()))
	{
		buyCard(NUMBER, piece);
		shop.at(NUMBER)->setVisible(false);
		shop.at(NUMBER)->setEnabled(false);
	}
}

void PlayScene::menuPieceCardCallBack3(Ref* sender)
{
	const unsigned int NUMBER = 2;
	ChessPiece* piece = shopModel->getPieceList()->at(NUMBER);
	//����
	if (shopModel->qualification(playerA->getMoney(), playerA->getMaxPieceStorage(), playerA->getPlayerPiecePossesion()->size(), piece->getPiecePerCost()))
	{
		buyCard(NUMBER, piece);
		shop.at(NUMBER)->setVisible(false);
		shop.at(NUMBER)->setEnabled(false);
	}
}

void PlayScene::menuPieceCardCallBack4(Ref* sender)
{
	const unsigned int NUMBER = 3;
	ChessPiece* piece = shopModel->getPieceList()->at(NUMBER);
	//����
	if (shopModel->qualification(playerA->getMoney(), playerA->getMaxPieceStorage(), playerA->getPlayerPiecePossesion()->size(), piece->getPiecePerCost()))
	{
		buyCard(NUMBER, piece);
		shop.at(NUMBER)->setVisible(false);
		shop.at(NUMBER)->setEnabled(false);
	}
}

//װ���� 
void PlayScene::menuPieceCardCallBack5(Ref* sender)
{
	const unsigned int NUMBER = 4;
	ChessPiece* piece = shopModel->getPieceList()->at(NUMBER);
	//����
	if (shopModel->qualification(playerA->getMoney(), playerA->getMaxPieceStorage(), playerA->getPlayerPiecePossesion()->size(), piece->getPiecePerCost()))
	{
		buyCard(NUMBER, piece);
		shop.at(NUMBER)->setVisible(false);
		shop.at(NUMBER)->setEnabled(false);
	}
}

void PlayScene::buyCard(const unsigned int num, ChessPiece* piece)
{
	// �����Ӧ�÷����ڱ�ս�����ĸ�λ��
	int i = 0;
	for (i; i < 8; i++)
	{
		if (chessBoardModel->getPlayerA_PreZone_Pieces()->at(i) == nullptr)
		{
			break;
		}
	}
	// ����ģ�����
	chessBoardModel->getPlayerA_PreZone_Pieces()->at(i) = piece;
	PieceCoordinate coordinate;
	coordinate.setX(i + 1);
	coordinate.setY(0);
	chessBoardModel->getPlayerA_PreZone_Pieces()->at(i)->setPrtCoordinate(&coordinate);
	// �������Ϣ����
	playerA->addToPiecePossesion(piece);
	playerA->setMoney(-1 * piece->getPiecePerCost());
	playerA->retain();
	// ���ӻ����
	auto visiblePiece = createChessPiece(shopModel->getPieceList()->at(num)->getPieceName(), shopModel->getPieceList()->at(num)->getPicPath(), Vec2(i + 1, 0), 0);
	pieceBoard[0][i + 1] = visiblePiece;
	playLayer->addChild(pieceBoard[0][i + 1], 7);
}

void PlayScene::menuFreshShopCallBack(Ref* sender)
{
	auto config = ConfigController::getInstance();

	if (playerA->getMoney() >= 2) // �������ˢ��
	{
		// ����ģ�͸���
		playerA->setMoney(-2);
		shopModel->refresh();

		// ���ӻ�����
		Vec2 position = Vec2(-config->getPx()->x * 45, -config->getPx()->y * 45);
		unsigned int i = 0;
		for (vector<MenuItemSprite*>::iterator it = shop.begin(); it != shop.end() && i < shop.size();)
		{
			//shop.at(i)->removeFromParent();
			(*it)->removeFromParent();
			it = shop.erase(it);

		}
		for (auto chessPtr : shop) {

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
}

void PlayScene::menuBuyExpCallBack(Ref* sender)
{
	// ����ģ�͸���
	playerA->promote();
	// ���ӻ�����
}

int PlayScene::onTouchBegan(Touch* touch, Event* event)
{
	Vec2 position = touch->getLocation();
	if (position.x > chessBoard[1][1]->getPositionX() && position.x < chessBoard[1][9]->getPositionX() &&
		position.y > chessBoard[1][1]->getPositionY() && position.y < chessBoard[5][1]->getPositionY()) // ���������ս����
	{
		if (mouseLiftPiece != nullptr && mouseLiftPiece->getTag() % 10 == 0) // �Ѿ�������Ǳ�ս������
		{
			return READY_TO_WAR;
		}
		else if (mouseLiftPiece != nullptr && mouseLiftPiece->getTag() % 10 != 0) // �Ѿ��������ս��������
		{
			return WAR_TO_WAR;
		}
		else // δ��������
		{
			return NO_LIFT_CLICK_WAR;
		}
		return IN_WAR_ZONE;
	}
	else if (position.x > chessBoard[0][1]->getPosition().x && position.x < chessBoard[0][9]->getPosition().x &&
			 position.y > chessBoard[0][1]->getPosition().y && position.y < chessBoard[1][1]->getPosition().y)
	{
		if (mouseLiftPiece != nullptr && mouseLiftPiece->getTag() % 10 == 0) // �Ѿ�������Ǳ�ս������
		{
			return READY_TO_READY;
		}
		else if (mouseLiftPiece != nullptr && mouseLiftPiece->getTag() % 10 != 0) // �Ѿ��������ս��������
		{
			return WAR_TO_READY;
		}
		else // δ��������
		{
			return NO_LIFT_CLICK_READY;
		}
		return IN_READY_ZONE;
	}
	else
	{
		return NOT_IN_BOARD;
	}
}

void PlayScene::onTouchEnded(Touch* touch, Event* event)
{
	int clickType = PlayScene::onTouchBegan(touch, event);
	Vec2 position = touch->getLocation();
	PieceCoordinate logPosition = coordingRevert(CoordinateType::real, position);
	
	switch (clickType)
	{
		case NO_LIFT_CLICK_WAR:
			if (chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1) != nullptr && mouseLiftPiece == nullptr)
			{
				int tag = 100 + 10 * logPosition.getY() + logPosition.getX();
				mouseLiftPiece = pieceBoard[logPosition.getY()][logPosition.getX()];
				mouseLiftPiece->setOpacity(70);
			}
			break;
		case NO_LIFT_CLICK_READY:
			if (chessBoardModel->getPlayerA_PreZone_Pieces()->at(logPosition.getX() - 1) != nullptr && mouseLiftPiece == nullptr)
			{
				int tag = 100 + logPosition.getX();
				mouseLiftPiece = pieceBoard[0][logPosition.getX()];
				mouseLiftPiece->setOpacity(70);
			}
			break;
		case WAR_TO_WAR:
			if (chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1) == nullptr && mouseLiftPiece != nullptr)
			{
				PieceCoordinate originPosition;
				originPosition.setX((mouseLiftPiece->getTag() - 100) / 10);
				originPosition.setY((mouseLiftPiece->getTag() - 100) % 10);
				// ����ģ���ƶ�
				chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1) = chessBoardModel->getWarZonePieces(originPosition.getY() - 1)->at(originPosition.getX() - 1);
				chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1)->retain();
				chessBoardModel->getWarZonePieces(originPosition.getY() - 1)->at(originPosition.getX() - 1) = nullptr;
				// �����Ϣ����
				for (int i = 0; i < playerA->getPlayerPieceBattle()->size(); i++)
				{
					if (playerA->getPlayerPieceBattle()->at(i)->getPrtCoordinate() == originPosition)
					{
						playerA->getPlayerPieceBattle()->at(i)->setPrtCoordinate(&logPosition);
					}
				}
				// ���ӻ��ƶ�
				ChessPiece* visiblePiece = chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1);
				pieceBoard[originPosition.getY()][originPosition.getX()]->removeFromParent();
				pieceBoard[logPosition.getY()][logPosition.getX()] = createChessPiece(visiblePiece->getPieceName(), visiblePiece->getPicPath(), Vec2(logPosition.getX(), logPosition.getY()), 1);
				playLayer->addChild(pieceBoard[logPosition.getY()][logPosition.getX()], 7);
				mouseLiftPiece = nullptr;
				pieceBoard[originPosition.getY()][originPosition.getX()] = nullptr;
			}
			break;
		case WAR_TO_READY:
			if (chessBoardModel->getPlayerA_PreZone_Pieces()->at(logPosition.getX() - 1) == nullptr && mouseLiftPiece != nullptr)
			{
				PieceCoordinate originPosition;
				originPosition.setX((mouseLiftPiece->getTag() - 100) / 10);
				originPosition.setY((mouseLiftPiece->getTag() - 100) % 10);
				// ����ģ���ƶ�
				chessBoardModel->getPlayerA_PreZone_Pieces()->at(logPosition.getX() - 1) = chessBoardModel->getWarZonePieces(originPosition.getY() - 1)->at(originPosition.getX() - 1);
				chessBoardModel->getPlayerA_PreZone_Pieces()->at(logPosition.getX() - 1)->retain();
				chessBoardModel->getWarZonePieces(originPosition.getY() - 1)->at(originPosition.getX() - 1) = nullptr;
				// �����Ϣ����
				playerA->addToPiecePossesion(chessBoardModel->getPlayerA_PreZone_Pieces()->at(logPosition.getX() - 1));
				for (int i = 0; i < playerA->getPlayerPieceBattle()->size(); i++)
				{
					if (playerA->getPlayerPieceBattle()->at(i)->getPrtCoordinate() == originPosition)
					{
						playerA->deleteFromBattleByID(i);
					}
				}
				// ���ӻ��ƶ�
				ChessPiece* visiblePiece = chessBoardModel->getPlayerA_PreZone_Pieces()->at(logPosition.getX() - 1);
				pieceBoard[originPosition.getY()][originPosition.getX()]->removeFromParent();
				pieceBoard[0][logPosition.getX()] = createChessPiece(visiblePiece->getPieceName(), visiblePiece->getPicPath(), Vec2(logPosition.getX(), logPosition.getY()), 0);
				playLayer->addChild(pieceBoard[0][logPosition.getX()], 7);
				mouseLiftPiece = nullptr;
				pieceBoard[originPosition.getY()][originPosition.getX()] = nullptr;
			}
			break;
		case READY_TO_READY:
			if (chessBoardModel->getPlayerA_PreZone_Pieces()->at(logPosition.getX() - 1) == nullptr && mouseLiftPiece != nullptr)
			{
				PieceCoordinate originPosition;
				originPosition.setX((mouseLiftPiece->getTag() - 100) / 10);
				originPosition.setY((mouseLiftPiece->getTag() - 100) % 10);
				// ����ģ���ƶ�
				chessBoardModel->getPlayerA_PreZone_Pieces()->at(logPosition.getX() - 1) = chessBoardModel->getPlayerA_PreZone_Pieces()->at(originPosition.getX() - 1);
				chessBoardModel->getPlayerA_PreZone_Pieces()->at(logPosition.getX() - 1)->retain();
				chessBoardModel->getPlayerA_PreZone_Pieces()->at(originPosition.getX() - 1) = nullptr;
				// �����Ϣ����
				for (int i = 0; i < playerA->getPlayerPiecePossesion()->size(); i++)
				{
					if (playerA->getPlayerPiecePossesion()->at(i)->getPrtCoordinate() == originPosition)
					{
						playerA->getPlayerPiecePossesion()->at(i)->setPrtCoordinate(&logPosition);
					}
				}
				// ���ӻ��ƶ�
				ChessPiece* visiblePiece = chessBoardModel->getPlayerA_PreZone_Pieces()->at(logPosition.getX() - 1);
				pieceBoard[0][originPosition.getX()]->removeFromParent();
				pieceBoard[0][logPosition.getX()] = createChessPiece(visiblePiece->getPieceName(), visiblePiece->getPicPath(), Vec2(logPosition.getX(), logPosition.getY()), 0);
				playLayer->addChild(pieceBoard[0][logPosition.getX()], 7);
				mouseLiftPiece = nullptr;
				pieceBoard[0][originPosition.getX()] = nullptr;
			}
			break;
		case READY_TO_WAR:
			if (chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1) == nullptr && mouseLiftPiece != nullptr && playerA->getPlayerPieceBattle()->size() < playerA->getMaxPieceBattle())
			{
				PieceCoordinate originPosition;
				originPosition.setX((mouseLiftPiece->getTag() - 100) / 10);
				originPosition.setY((mouseLiftPiece->getTag() - 100) % 10);
				// ����ģ���ƶ�
				chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1) = chessBoardModel->getPlayerA_PreZone_Pieces()->at(originPosition.getX() - 1);
				chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1)->retain();
				chessBoardModel->getPlayerA_PreZone_Pieces()->at(originPosition.getX() - 1) = nullptr;
				// �����Ϣ����
				playerA->addToPieceBattle(chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1));
				for (int i = 0; i < playerA->getPlayerPiecePossesion()->size(); i++)
				{
					if (playerA->getPlayerPiecePossesion()->at(i)->getPrtCoordinate() == originPosition)
					{
						playerA->deleteFromPossesionByID(i);
					}
				}
				// ���ӻ��ƶ�
				ChessPiece* visiblePiece = chessBoardModel->getWarZonePieces(logPosition.getY() - 1)->at(logPosition.getX() - 1);
				pieceBoard[originPosition.getY()][originPosition.getX()]->removeFromParent();
				pieceBoard[logPosition.getY()][logPosition.getX()] = createChessPiece(visiblePiece->getPieceName(), visiblePiece->getPicPath(), Vec2(logPosition.getX(), logPosition.getY()), 1);
				playLayer->addChild(pieceBoard[logPosition.getY()][logPosition.getX()], 7);
				mouseLiftPiece = nullptr;
				pieceBoard[originPosition.getY()][originPosition.getX()] = nullptr;
			}
			break;
		case NOT_IN_BOARD:
			if (mouseLiftPiece != nullptr)
			{
				mouseLiftPiece->setOpacity(250);
				mouseLiftPiece = nullptr;
			}
			break;
		default:
			break;
	}
}

void PlayScene::onMouseMove(Event* event)
{
	EventMouse* e = (EventMouse*)event;
}
