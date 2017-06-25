#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
   
    if ( !Layer::init() )
    {
        return false;
    }
	initBG();
	initMenu();
    return true;
}

void HelloWorld::initBG()
{
	auto spr = Sprite::create("1.png");
	spr->setPosition(Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
	this->addChild(spr);
}

void HelloWorld::initMenu()
{
	auto item_0 = MenuItemFont::create("Play", CC_CALLBACK_1(HelloWorld::menuCallback, this));
	auto item_1 = MenuItemFont::create("Help", CC_CALLBACK_1(HelloWorld::menuCallback, this));
	auto item_2 = MenuItemFont::create("Option", CC_CALLBACK_1(HelloWorld::menuCallback, this));
	auto item_3 = MenuItemFont::create("Quit", CC_CALLBACK_1(HelloWorld::menuCallback, this));
	item_0->setTag(TAG_MENUITEM_PLAY);
	item_1->setTag(TAG_MENUITEM_HELP);
	item_2->setTag(TAG_MENUITEM_OPTION);
	item_3->setTag(TAG_MENUITEM_QUIT);
	auto menu = Menu::create(item_0, item_1, item_2, item_3, NULL);
	menu->alignItemsVerticallyWithPadding(20);
	this->addChild(menu);
}

void HelloWorld::menuCallback(Ref *sender)
{
	auto item = (MenuItem*)sender;
	switch (item->getTag())
	{
		case TAG_MENUITEM_PLAY:
		{
				auto scene = TransitionFadeTR::create(1.0,GameScene::createScene());
				Director::getInstance()->replaceScene(scene);
		}
		case TAG_MENUITEM_HELP:
			break;
		case TAG_MENUITEM_OPTION:
			break;
		case TAG_MENUITEM_QUIT:
			Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			exit(0);
#endif
			break;
		default:
			break;
	}
}