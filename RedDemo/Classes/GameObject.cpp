#include "GameObject.h"
#include "cocos2d.h"
#include <Box2D/Box2D.h>

USING_NS_CC;

GameObject::GameObject(GameWorld& world) : 
	gameWorld(world),
	RATIO(100) {}

void GameObject::physicsTick(float physicsTickLength) {
	this->oldPosition = this->newPosition;
	this->newPosition = Vec2(this->getPhysicsBody()->GetPosition().x, this->getPhysicsBody()->GetPosition().y);
}

bool GameObject::hasPhysics() const {
	return this->physicsBody != nullptr;
}

void GameObject::setPhysicsBody(b2Body* body) {
	this->physicsBody = body;
}

GameWorld& GameObject::getGameWorld() {
	return this->gameWorld;
}

b2Body* GameObject::getPhysicsBody() {
	return this->physicsBody;
}

void GameObject::updateGraphics(float interpolation) {
	if (this->hasPhysics()) {
		Vec2 interpolated = (oldPosition * (1.0f - interpolation) + newPosition * (interpolation)) * RATIO;
		this->graphics->setPosition(interpolated);
		this->graphics->setRotation(-this->physicsBody->GetAngle()/3.14f*180);
	}
}

cocos2d::Node* GameObject::getGraphics() {
	return this->graphics;
}