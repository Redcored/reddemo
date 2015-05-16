#include "Platform.h"

USING_NS_CC;

Platform::Platform(Layer* layer) {
	setupGraphics();
	addToLayer(layer);
}

void Platform::addToLayer(Layer* layer) const {
	layer->addChild(this->graphics, 0);
}

void Platform::setupGraphics() {
	this->graphics = DrawNode::create();
	this->graphics->drawSolidRect(Point(-1920/2, -150), Point(1920/2, 150), Color4F(Color3B::WHITE));
	this->graphics->setPosition(Point(1920/2, 150));
	auto body = PhysicsBody::createBox(Size(1920,300), PHYSICSBODY_MATERIAL_DEFAULT);
	body->setDynamic(false);
	this->graphics->setPhysicsBody(body);
}