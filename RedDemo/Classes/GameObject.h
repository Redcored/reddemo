#pragma once

#include "cocos2d.h"

class b2Body;
class GameWorld;

class GameObject {

public:
	GameObject(GameWorld& world);

	bool hasPhysics() const;
	void setPhysicsBody(b2Body* body);

	// Update Graphics Coordinates to Correspond the ones in physicsBody
	void updateGraphics(float interpolation);
	void physicsTick(float physicsTickLength);

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