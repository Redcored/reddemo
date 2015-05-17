#include "GameObject.h"

GameObject::GameObject(GameScene* scene) {
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