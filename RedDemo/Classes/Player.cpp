#include "Player.h"

USING_NS_CC;

namespace {
	const float BALL_RADIUS = 100.0f;
	const float BALL_ANGLE = 0.0f;
	const float ACCELERATION = 200;
	const unsigned int BALL_SEGMENTS = 64;
};

Player::Player() {
	setupGraphics();
	setupPhysics();
	startKeyboardListener();
	this->setPosition(Vec2(1920 / 2, 1080 / 2));
}

void Player::setupGraphics() {
	DrawNode* node = DrawNode::create();
	node->drawCircle(Vec2::ZERO, BALL_RADIUS, BALL_ANGLE, BALL_SEGMENTS, true, Color4F(Color3B::ORANGE));
	this->addChild(node);
	this->graphics = node;
}

void Player::setupPhysics() {
	auto body = PhysicsBody::createCircle(BALL_RADIUS, PhysicsMaterial(1, 1, 1));
	body->setMass(1);
	this->setPhysicsBody(body);
}

void Player::keyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	PhysicsBody* body = event->getCurrentTarget()->getPhysicsBody();

	switch (keyCode){
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
		body->applyForce(Vec2(-ACCELERATION, 0));
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
		body->applyForce(Vec2(ACCELERATION, 0));
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
		body->applyForce(Vec2(0, ACCELERATION));
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_S:
		body->applyForce(Vec2(0, -ACCELERATION));
		break;
	}
}

void Player::keyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	PhysicsBody* body = event->getCurrentTarget()->getPhysicsBody();

	//body->setVelocity(body->getVelocity() + Vec2(-300, 0));
	//body->applyImpulse(Vect(-300, 0));
	//body->applyTorque(1000);

	switch (keyCode){
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
		body->applyForce(Vec2(ACCELERATION, 0));
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
		body->applyForce(Vec2(-ACCELERATION, 0));
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
		body->applyForce(Vec2(0, -ACCELERATION));
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_S:
		body->applyForce(Vec2(0, ACCELERATION));
		break;
	}
}

void Player::startKeyboardListener() {

	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = CC_CALLBACK_2(Player::keyPressed, this);
	eventListener->onKeyReleased = CC_CALLBACK_2(Player::keyReleased, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
}