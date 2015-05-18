#pragma once

#include <vector>
#include <cocos2d.h>

class GameObject;
class b2World;

class GameWorld {

public:
	GameWorld(cocos2d::Node& graphicsNode);

	void update(float deltaTime);
	b2World* getPhysics();

private:
	GameWorld();

	cocos2d::Node& graphicsNode;

	b2World* physics;
	float updateTimeAccumulator;
	const float physicsTickDuration;

	std::vector<GameObject*> gameObjects;
};