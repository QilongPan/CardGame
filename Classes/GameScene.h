#pragma once
#include"cocos2d.h"
#include"HelloWorldScene.h"
#include"time.h"
USING_NS_CC;
#define TAG_LABEL_CARD 0
#define TAG_LABEL_LIFE 1
#define TAG_LABEL_READY 2
#define TAG_LABEL_START 3
#define TAG_SPRITE_O 4
#define TAG_SPRITE_X 5
#define TAG_LABEL_GAMEOVER 6
#define TAG_LABEL_GAMECLEAR 7
#define TAG_MENU 8
#define TAG_SPRITE_CARD 10

class GameScene :public Layer
{
public:
	GameScene();
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);
	Size winSize;
	int cardOK, life;
	int card[4];
	int countCard;
	bool isTouch;
	void initGameData();
	void initBG();
	void initTopMenuLabel();
	void setLabelCard();
	void setLabelLife();
	void initCard();

	void initReady();
	void initStart();
	void actionReady();
	void endReady();
	void actionStart();
	void endStart();
	void actionCard();
	void endCard();

	bool onTouchBegan(Touch *touch, Event *unused_event);
	void initO();
	void initX();
	void actionOX(bool isO);
	void endOX();

	void actionGameEnd(bool isGameClear);
	void endGameEnd();
	void initGameClear();
	void initGameOver();
	void initMenu();
	void actionMenu(bool isShow);
	void menuCallBack(Ref *sender);
	~GameScene();
};

