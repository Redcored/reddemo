#pragma once

#include "cocos2d.h"
#include "Platform.h"

class GameScene : public cocos2d::Layer
{
public:

	// Cocos 2D's management functions.
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);

private:
	cocos2d::Label* label;
	std::vector<GameObject*> worldObjects;
	cocos2d::PhysicsWorld* sceneWorld;

	void update(float deltaTime);
	void initMenu();
	void pauseCallback(Ref* pSender);
	void setPhysicsWorld(cocos2d::PhysicsWorld* world);
};

