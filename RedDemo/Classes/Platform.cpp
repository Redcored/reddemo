#include "Platform.h"

USING_NS_CC;

Platform::Platform() {
	setupGraphics();
	setupPhysics();
}

void Platform::setupGraphics() {
	auto node = DrawNode::create();
	node->drawSolidRect(Point(-1920 / 2, -100), Point(1920 / 2, 100), Color4F(Color3B::WHITE));
	this->addChild(node);
	this->graphics = node;
}

void Platform::setupPhysics() {
	auto body = PhysicsBody::createBox(Size(1920, 200), PHYSICSBODY_MATERIAL_DEFAULT);
	body->setDynamic(false);
	this->setPhysicsBody(body);
}