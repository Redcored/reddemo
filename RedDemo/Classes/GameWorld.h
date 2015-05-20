#pragma once

#include <vector>
#include <cocos2d.h>
#include <Box2D\Box2D.h>

class GameObject;
class b2World;

class GameWorld : b2ContactListener {

public:
	GameWorld(cocos2d::Node& graphicsNode);

	void update(float deltaTime);
	b2World* getPhysics();
	void BeginContact(b2Contact* contact) override;
private:
	GameWorld();

	cocos2d::Node& graphicsNode;

	b2World* physics;
	float updateTimeAccumulator;
	const float physicsTickDuration;

	std::vector<GameObject*> gameObjects;
};