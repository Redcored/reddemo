#include "Platform.h"
#include "GameScene.h"
#include <Box2D\Box2D.h>

USING_NS_CC;

Platform::Platform(GameScene* scene) : GameObject(scene) {
	setupGraphics();
	setupPhysics();
}

void Platform::setupGraphics() {
	auto node = DrawNode::create();
	node->drawSolidRect(Point(-1920 / 2, -100), Point(1920 / 2, 100), Color4F(Color3B::WHITE));
	this->getGameWorld()->addChild(node);
	this->graphics = node;
}

void Platform::setupPhysics() {
	b2Body* body;

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(50, 30);
	bodyDef.userData = this;
	body = this->getGameWorld()->getPhysics()->CreateBody(&bodyDef);
	
	b2PolygonShape shape;
	shape.SetAsBox(50, 10);

	b2FixtureDef shapeDef;
	shapeDef.shape = &shape;
	shapeDef.density = 10.0f;
	shapeDef.friction = 0.4f;
	shapeDef.restitution = 0.1f;

	body->CreateFixture(&shapeDef);
	this->setPhysicsBody(body);
}