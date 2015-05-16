#include "Player.h"

USING_NS_CC;

namespace {
	const float BALL_RADIUS = 100.0f;
	const float BALL_ANGLE = 0.0f;
	const unsigned int BALL_SEGMENTS = 64;
};

Player::Player(cocos2d::Layer* layer) {
	setupGraphics();
	setupPhysics();
	addToLayer(layer);
	startKeyboardListener(layer);
}

void Player::addToLayer(cocos2d::Layer* layer) const {
	layer->addChild(this->graphics);
}

void Player::setupGraphics() {
	this->graphics = DrawNode::create();
	this->graphics->drawSolidCircle(Vec2::ZERO, BALL_RADIUS, BALL_ANGLE, BALL_SEGMENTS, Color4F(Color3B::ORANGE));
	this->graphics->setPosition(1920/2, 1080/2);
}

void Player::setupPhysics() {
	auto body = PhysicsBody::createCircle(BALL_RADIUS, PHYSICSBODY_MATERIAL_DEFAULT);
	this->graphics->setPhysicsBody(body);
}

void Player::startKeyboardListener(cocos2d::Layer* layer) {
	auto eventListener = EventListenerKeyboard::create();

    eventListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event){
		PhysicsBody* body = event->getCurrentTarget()->getPhysicsBody();

		switch(keyCode){
			case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			case EventKeyboard::KeyCode::KEY_A:
				body->setVelocity(body->getVelocity() + Vec2(-300, 0));
				break;
			case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			case EventKeyboard::KeyCode::KEY_D:
				body->setVelocity(body->getVelocity() + Vec2(300, 0));
				break;
			case EventKeyboard::KeyCode::KEY_UP_ARROW:
			case EventKeyboard::KeyCode::KEY_W:
				body->setVelocity(body->getVelocity() + Vec2(0, 300));
				break;
			case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			case EventKeyboard::KeyCode::KEY_S:
				body->setVelocity(body->getVelocity() + Vec2(0, -300));
				break;
		}
    };

	layer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this->graphics);
}