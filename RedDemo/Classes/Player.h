#pragma once
#include "cocos2d.h"
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player(GameWorld& world);
	virtual void acceptCollision(GameObject* gameObject) override;
	virtual void collide(Platform& platform) override;
private:
	void setupGraphics();
	void setupPhysics();
	void physicsTick(float physicsTickLength) override;
	void startKeyboardListener();
	void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	cocos2d::Vec2 forceVector;
};