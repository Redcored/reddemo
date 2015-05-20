#pragma once

#include "cocos2d.h"

class b2Body;
class GameWorld;
class Platform;
class Player;

class GameObject {

public:
	GameObject(GameWorld& world);

	bool hasPhysics() const;
	void setPhysicsBody(b2Body* body);

	// Update Graphics Coordinates to Correspond the ones in physicsBody
	void updateGraphics(float interpolation);
	virtual void physicsTick(float physicsTickLength);

	// Accept collision function that each GameObject has to implement
	virtual void acceptCollision(GameObject* gameObject) = 0;

	// Collide functions that GameObjects can inherit if they wish to do so
	virtual void collide(Platform& platform);
	virtual void collide(Player& player);

	GameWorld& getGameWorld();
	cocos2d::Node* getGraphics();
	b2Body* getPhysicsBody();

protected:
	cocos2d::Node* graphics;
	cocos2d::Vec2 oldPosition;
	cocos2d::Vec2 newPosition;

	// PhysicsMeters to Pixels ratio
	const float RATIO;
private:
	GameWorld& gameWorld;
	b2Body* physicsBody;
};