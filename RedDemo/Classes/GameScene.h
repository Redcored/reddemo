#pragma once

#include "cocos2d.h"

class GameWorld;

class GameScene : public cocos2d::Layer
{
public:

	// Cocos 2D's management functions.
	static cocos2d::Scene* createScene();

	virtual bool init();
	CREATE_FUNC(GameScene);

private:
	GameWorld* gameWorld;

	cocos2d::Label* label;

	void update(float deltaTime);
	void initMenu();
	void pauseCallback(Ref* pSender);
};

