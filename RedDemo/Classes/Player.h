#pragma once
#include "cocos2d.h"
#include "GameObject.h"

class Player :
	public GameObject
{
public:
	Player(cocos2d::Layer* layer);

protected:
	virtual void addToLayer(cocos2d::Layer* layer) const;

private:
	void setupGraphics();
	void setupPhysics();
	void startKeyboardListener(cocos2d::Layer* layer);
	cocos2d::DrawNode* graphics;
};