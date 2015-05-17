#pragma once

#include "cocos2d.h"

class b2Body;
class GameScene;

class GameObject {

public:
	GameObject(GameScene* scene);

	bool hasPhysics() const;
	void setPhysicsBody(b2Body* body);
	
	GameScene* getGameWorld();
	b2Body* getPhysicsBody();

protected:
	cocos2d::Node* graphics;

private:
	GameScene* gameWorld;
	b2Body* physicsBody;

};