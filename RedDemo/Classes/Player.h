#pragma once
#include "cocos2d.h"
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player();

private:
	void setupGraphics();
	void setupPhysics();
	void startKeyboardListener();
	void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
};