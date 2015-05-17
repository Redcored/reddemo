#include "Platform.h"
#include "GameScene.h"
#include <Box2D\Box2D.h>

USING_NS_CC;

namespace {
	const float WIDTH = 19.2f;
	const float HEIGHT = 2.0f;
};


Platform::Platform(GameScene* scene) : GameObject(scene) {
	setupGraphics();
	setupPhysics();
}

void Platform::setupGraphics() {
	auto node = DrawNode::create();
	node->drawSolidRect(Point(-WIDTH * RATIO/2, -HEIGHT*RATIO/2), Point(WIDTH * RATIO/2, HEIGHT * RATIO/2), Color4F(Color3B::WHITE));
	this->getGameWorld()->addChild(node);
	this->graphics = node;
}

void Platform::setupPhysics() {
	b2Body* body;

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(WIDTH/2, HEIGHT/2);
	bodyDef.userData = this;
	body = this->getGameWorld()->getPhysics()->CreateBody(&bodyDef);
	
	b2PolygonShape shape;
	shape.SetAsBox(WIDTH/2, HEIGHT/2);

	b2FixtureDef shapeDef;
	shapeDef.shape = &shape;
	shapeDef.density = 10.0f;
	shapeDef.friction = 0.4f;
	shapeDef.restitution = 0.1f;

	body->CreateFixture(&shapeDef);
	this->setPhysicsBody(body);
}