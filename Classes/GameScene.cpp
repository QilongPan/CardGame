#include "GameScene.h"


GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
	isTouch = false;
	initGameData();
	initTopMenuLabel();
	initCard();
	initReady();
	initStart();
	actionReady();
	initX();
	initO();
	return true;
}
//初始化游戏数据
void GameScene::initGameData()
{
	winSize = Director::getInstance()->getWinSize();		//获取画面大小
	cardOK = 0;
	life = 3;
	srand(time(NULL));
	for (int i = 0; i < 4; i++)
	{
		card[i] = rand() % 6;
	}
	countCard = 0;
}

void GameScene::initBG()
{
	auto spr = Sprite::create("background2.png");
	spr->setPosition(Point(winSize.width / 2, winSize.height / 2));
	this->addChild(spr);
}

void GameScene::initTopMenuLabel()
{
	auto label_0 = Label::createWithSystemFont("", "", 20);
	label_0->setAnchorPoint(Point(0, 1));
	label_0->setPosition(Point(10, winSize.height - 10));
	label_0->setTag(TAG_LABEL_CARD);
	label_0->setColor(Color3B::BLACK);
	this->addChild(label_0);
	auto label_1 = Label::createWithSystemFont("", "", 20);
	label_1->setAnchorPoint(Point(1, 1));
	label_1->setPosition(Point(winSize.width - 10, winSize.height - 10));
	label_1->setTag(TAG_LABEL_LIFE);
	label_1->setColor(Color3B::BLACK);
	this->addChild(label_1);
	setLabelCard();
	setLabelLife();
}

void GameScene::setLabelCard()
{
	auto label = (Label*)this->getChildByTag(TAG_LABEL_CARD);
	label->setString(StringUtils::format("CARD:%d/4", cardOK));
}

void GameScene::setLabelLife()
{
	auto label = (Label*)this->getChildByTag(TAG_LABEL_LIFE);
	label->setString(StringUtils::format("LIFE:%d", life));
}

void GameScene::initCard()
{
	for (int i = 0; i < 6; i++)
	{
		auto spr = Sprite::create("HelloWorld.png");
		spr->setPosition(Point(winSize.width / 2 - 60 + 60 * 2 * (i % 2), winSize.height / 2 + 120 - 120 * (i / 2)));
		this->addChild(spr);
		auto sprFront = Sprite::create(StringUtils::format("card_%d.png", (i + 1)));
		sprFront->setPosition(Point(winSize.width / 2 - 60 + 60 * 2 * (i % 2), winSize.height / 2 + 120 - 120 * (i / 2)));
		sprFront->setVisible(false);
		sprFront->setTag(TAG_SPRITE_CARD + i);
		this->addChild(sprFront);
	}
}

void GameScene::initReady()
{
	auto label = Label::createWithSystemFont("READY", "", 80);
	label->setPosition(Point(winSize.width / 2, winSize.height / 2));
	label->setTag(TAG_LABEL_READY);
	label->setColor(Color3B::BLACK);
	label->setScale(0.0);
	this->addChild(label);
}

void GameScene::initStart()
{
	auto label = Label::createWithSystemFont("START", "", 80);
	label->setPosition(Point(winSize.width / 2, winSize.height / 2));
	label->setTag(TAG_LABEL_START);
	label->setColor(Color3B::BLACK);
	label->setScale(0.0);
	this->addChild(label);
}

void GameScene::actionReady()
{
	auto action = Sequence::create(ScaleTo::create(1.0, 1.0),
		DelayTime::create(2.0),
		ScaleTo::create(1.0, 0.0),
		CallFunc::create(CC_CALLBACK_0(GameScene::endReady, this)),
		NULL);
	auto label = (Label*)this->getChildByTag(TAG_LABEL_READY);
	label->runAction(action);
}

void GameScene::endReady()
{
	actionStart();
}

void GameScene::actionStart()
{
	auto action = Sequence::create(
		ScaleTo::create(1.0, 1.0),
		DelayTime::create(2.0),
		ScaleTo::create(1.0, 0.0),
		CallFunc::create(CC_CALLBACK_0(GameScene::endStart, this)),
		NULL);
	auto label = (Label*)this->getChildByTag(TAG_LABEL_START);
	label->runAction(action);
}

void GameScene::endStart()
{
	actionCard();
}

void GameScene::actionCard()
{
	for (int i = 0; i < 4; i++){
		auto action = Sequence::create(
			DelayTime::create(3.0*i),
			Show::create(),
			DelayTime::create(2.0),
			Hide::create(),
			NULL);
		auto spr = (Sprite*)this->getChildByTag(TAG_LABEL_CARD + card[i]);
		spr->runAction(action);
	}
	auto action = Sequence::create(
		DelayTime::create(1.0),
		CallFunc::create(CC_CALLBACK_0(GameScene::endCard, this)),
		NULL);
	this->runAction(action);
}

void GameScene::endCard()
{
	isTouch = true;
}

bool GameScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	if (!isTouch)
		return true;
	Point location = touch->getLocation();
	for (int i = 0; i < 6; i++)
	{
		auto spr = (Sprite*)this->getChildByTag(TAG_SPRITE_CARD + i);
		Rect sprRect = spr->getBoundingBox();
		if (sprRect.containsPoint(location))
		{
			isTouch = false;
			auto action = Sequence::create(
				Show::create(),
				DelayTime::create(0.5),
				Hide::create(),
				NULL);
			spr->runAction(action);
			if (i == card[countCard])
			{
				cardOK++;
				countCard++;
				setLabelCard();
				actionOX(true);
			}
			else
			{
				life--;
				setLabelLife();
				actionOX(false);
			}
		}
	}
	return true;
}

void GameScene::initO()
{
	auto spr = Sprite::create("o.png");
	spr->setPosition(Point(winSize.width / 2, winSize.height / 2));
	spr->setTag(TAG_SPRITE_O);
	spr->setVisible(false);
	this->addChild(spr);
}

void GameScene::initX()
{
	auto spr = Sprite::create("o.png");
	spr->setPosition(Point(winSize.width / 2, winSize.height / 2));
	spr->setTag(TAG_SPRITE_X);
	spr->setVisible(false);
	this->addChild(spr);
}

void GameScene::actionOX(bool isO)
{
	auto action = Sequence::create(
		Show::create(),
		DelayTime::create(0.5),
		Hide::create(),
		CallFunc::create(CC_CALLBACK_0(GameScene::endOX, this)),
		NULL);
	Sprite* spr;
	if (isO){
		spr = (Sprite*)this->getChildByTag(TAG_SPRITE_O);
	}
	else
	{
		spr = (Sprite*)this->getChildByTag(TAG_SPRITE_X);
	}
	spr->runAction(action);
}

void GameScene::endOX(){
	if (!(cardOK == 4 || life == 0))
	{
		isTouch = true;
	}
}


void GameScene::actionGameEnd(bool isGameClear)
{
	isTouch = false;
	auto action = Sequence::create(
		DelayTime::create(0.5),
		Show::create(),
		EaseBounceOut::create(MoveTo::create(1.0, Point(winSize.width / 2, winSize.height / 2))),
		DelayTime::create(1.0),
		Hide::create(),
		Place::create(Point(winSize.width / 2, winSize.height + 50)),
		CallFunc::create(CC_CALLBACK_0(GameScene::endGameEnd, this)),
		NULL);
	Label *label;
	if (isGameClear)
	{
		label = (Label *)this->getChildByTag(TAG_LABEL_GAMECLEAR);

	}
	else
	{
		label = (Label *)this->getChildByTag(TAG_LABEL_GAMEOVER);
	}
	label->runAction(action);
}

void GameScene::endGameEnd()
{
	actionMenu(true);
}


void GameScene::initGameClear()
{
	auto label = Label::createWithSystemFont("GAME CLEAR", "", 50);
	label->setPosition(Point(winSize.width / 2, winSize.height + 50));
	label->setTag(TAG_LABEL_GAMECLEAR);
	label->setColor(Color3B::BLUE);
	label->setVisible(true);
	this->addChild(label);
}

void GameScene::initGameOver()
{
	auto label = Label::createWithSystemFont("GAME OVER", "", 50);
	label->setPosition(Point(winSize.width / 2, winSize.height + 50));
	label->setTag(TAG_LABEL_GAMEOVER);
	label->setColor(Color3B::RED);
	label->setVisible(false);
	this->addChild(label);
}

void GameScene::initMenu()
{
	auto item_0 = MenuItemFont::create("retry", CC_CALLBACK_1(GameScene::menuCallBack, this));
	auto item_1 = MenuItemFont::create("main menu", CC_CALLBACK_1(GameScene::menuCallBack, this));
	item_0->setTag(0);
	item_1->setTag(1);
	item_0->setColor(Color3B::BLACK);
	item_1->setColor(Color3B::BLACK);
	auto menu = Menu::create(item_0, item_1, NULL);
	menu->alignItemsHorizontallyWithPadding(50);
	menu->setPosition(Point(winSize.width / 2, 30));
	menu->setTag(TAG_MENU);
	menu->setVisible(false);
	this->addChild(menu);
}

void GameScene::actionMenu(bool isShow)
{
	auto menu = (Menu*)this->getChildByTag(TAG_MENU);
	menu->setVisible(isShow);
}

void GameScene::menuCallBack(Ref* sender)
{
	auto item = (MenuItemFont*)sender;
	if (item->getTag() == 0)
	{
		initGameData();
		setLabelCard();
		setLabelLife();
		actionMenu(false);
		actionReady();
	}
	else{
		Director::getInstance()->replaceScene(HelloWorld::createScene());
	}
}