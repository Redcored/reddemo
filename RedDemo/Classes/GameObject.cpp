#include "GameObject.h"
#include <Box2D/Box2D.h>

GameObject::GameObject(GameScene* scene) : RATIO(100) {
	this->gameWorld = scene;
}

bool GameObject::hasPhysics() const {
	return this->physicsBody != nullptr;
}

void GameObject::setPhysicsBody(b2Body* body) {
	this->physicsBody = body;
}

GameScene* GameObject::getGameWorld() {
	return this->gameWorld;
}

b2Body* GameObject::getPhysicsBody() {
	return this->physicsBody;
}

void GameObject::update() {
	if (this->hasPhysics()) {
		this->graphics->setPosition(this->physicsBody->GetPosition().x * RATIO, this->physicsBody->GetPosition().y * RATIO);
		this->graphics->setRotation(this->physicsBody->GetAngle());
	}
}

cocos2d::Node* GameObject::getGraphics() {
	return this->graphics;
}