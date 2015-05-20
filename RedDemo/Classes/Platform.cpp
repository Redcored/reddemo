#include "Platform.h"

#include <Box2D\Box2D.h>
#include "GameWorld.h"

USING_NS_CC;

Platform::Platform(GameWorld& world, const cocos2d::Size& size, const cocos2d::Vec2& position) :
	GameObject(world)
{
	setupGraphics(size);
	setupPhysics(size, position);
	this->newPosition = position;
	this->oldPosition = position;
	updateGraphics(0);
}

void Platform::setupGraphics(const cocos2d::Size& size) {
	auto node = DrawNode::create();
	node->drawSolidRect(Point(-size.width * RATIO/2, -size.height*RATIO/2), Point(size.width * RATIO/2, size.height * RATIO/2), Color4F(Color3B::WHITE));
	this->graphics = node;
}

void Platform::setupPhysics(const cocos2d::Size& size, const cocos2d::Vec2& position) {
	b2Body* body;

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.userData = this;
	body = this->getGameWorld().getPhysics()->CreateBody(&bodyDef);
	
	b2PolygonShape shape;
	shape.SetAsBox(size.width/2, size.height/2);

	b2FixtureDef shapeDef;
	shapeDef.shape = &shape;
	shapeDef.density = 10.0f;
	shapeDef.friction = 0.4f;
	shapeDef.restitution = 0.0f;

	body->CreateFixture(&shapeDef);
	this->setPhysicsBody(body);
}

void Platform::acceptCollision(GameObject* gameObject) {
	gameObject->collide(*this);
}