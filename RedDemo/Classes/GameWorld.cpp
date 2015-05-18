#include "GameWorld.h"

#include <Box2D\Box2D.h>
#include <cocos2d.h>
#include "GameObject.h"
#include "Player.h"
#include "Platform.h"

USING_NS_CC;

GameWorld::GameWorld(cocos2d::Node& graphicsNode) :
	graphicsNode(graphicsNode),
	physics(new b2World(b2Vec2(0, -9.81))),
	updateTimeAccumulator(0),
	physicsTickDuration(0.02)
{
	
	gameObjects.push_back(new Player(*this));
	gameObjects.push_back(new Platform(*this, Size(10.0f, 1.0f), Vec2((float)5.0f, 0)));
	for (int i = 0; i < 1000; i++) {
		float rand = random(0, 10);

		if (rand < 1) {}
		else if (rand < 6) {
			gameObjects.push_back(new Platform(*this, Size(10.0f, 1.0f), Vec2((float)10.0f * i, 10.8)));
			gameObjects.push_back(new Platform(*this, Size(10.0f, 1.0f), Vec2((float)10.0f * i, 0)));
		}
		else if (rand < 8) {
			gameObjects.push_back(new Platform(*this, Size(10.0f, 1.0f), Vec2((float)10.0f * i, 10.8)));
		}
		else {
			gameObjects.push_back(new Platform(*this, Size(10.0f, 1.0f), Vec2((float)10.0f * i, 0)));
		}
	}
	
	for (GameObject* o : gameObjects) {
		graphicsNode.addChild(o->getGraphics());
	}
}

void GameWorld::update(float deltaTime) {
	this->updateTimeAccumulator += deltaTime;

	while (this->updateTimeAccumulator >= physicsTickDuration) {

		// Performing the physics tick
		for (GameObject* o : gameObjects) {
			o->physicsTick(physicsTickDuration);
		}
		this->physics->Step(physicsTickDuration, 8, 3);

		this->updateTimeAccumulator -= physicsTickDuration;
	}

	float interpolation = this->updateTimeAccumulator / physicsTickDuration;
	for (GameObject* o : gameObjects) {
		gameObjects.at(0)->updateGraphics(interpolation);
	}
	float zoom = 1;
	graphicsNode.setPosition(-(gameObjects.at(0)->getGraphics()->getPosition().x - 500)*zoom, graphicsNode.getPosition().y);

	/*
	graphicsNode.setScale(zoom);
	*/
}

b2World* GameWorld::getPhysics() {
	return this->physics;
}