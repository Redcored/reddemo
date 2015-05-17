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
	void update();

	cocos2d::Node* getGraphics();
	
	GameScene* getGameWorld();
	b2Body* getPhysicsBody();

protected:
	cocos2d::Node* graphics;

	// PhysicsMeters to Pixels ratio
	const float RATIO;
private:
	GameScene* gameWorld;
	b2Body* physicsBody;
};