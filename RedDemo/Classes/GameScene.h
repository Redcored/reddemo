#pragma once

#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "Platform.h"

class GameScene : public cocos2d::Layer
{
public:

	// Cocos 2D's management functions.
	static cocos2d::Scene* createScene();

	b2World* getPhysics();

	virtual bool init();
	CREATE_FUNC(GameScene);

private:
	cocos2d::Label* label;
	b2World* physicsWorld;

	void update(float deltaTime);
	void initMenu();
	void pauseCallback(Ref* pSender);
	void setupPhysics();
};

