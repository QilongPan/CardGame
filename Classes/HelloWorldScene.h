#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include"GameScene.h"
USING_NS_CC;
#define TAG_MENUITEM_PLAY 0
#define TAG_MENUITEM_HELP 1
#define TAG_MENUITEM_OPTION 2
#define TAG_MENUITEM_QUIT 3

class HelloWorld : public Layer
{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);
	void initBG();
	void initMenu();
	void menuCallback(Ref* sender);
};

#endif // __HELLOWORLD_SCENE_H__
