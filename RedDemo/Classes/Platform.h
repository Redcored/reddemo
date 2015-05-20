#pragma once
#include "GameObject.h"

class Platform : public GameObject {

public:
	// Size in Game coordinates, not pixels!
	Platform(GameWorld& world, const cocos2d::Size& size, const cocos2d::Vec2& position);
	virtual void acceptCollision(GameObject* gameObject) override;
private:
	void setupGraphics(const cocos2d::Size& size);
	void setupPhysics(const cocos2d::Size& size, const cocos2d::Vec2& position);
};