#pragma once

#include "cocos2d.h"

class b2Body;
class GameScene;

class GameObject {

public:
	GameObject(GameScene* scene);

	bool hasPhysics() const;
	void setPhysicsBody(b2Body* body);

	// Update Graphics Coordinates to Correspond the ones in physicsBody
	void updateGraphics(float interpolation);
	void updatePhysics(float physicsTickLength);

	cocos2d::Node* getGraphics();
	
	GameScene* getGameWorld();
	b2Body* getPhysicsBody();

protected:
	cocos2d::Node* graphics;
	cocos2d::Vec2 oldPosition;
	cocos2d::Vec2 newPosition;

	// PhysicsMeters to Pixels ratio
	const float RATIO;
private:
	GameScene* gameWorld;
	b2Body* physicsBody;
};