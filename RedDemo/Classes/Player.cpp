#include "Player.h"
#include "GameScene.h"
#include <Box2D\Box2D.h>

USING_NS_CC;

namespace {
	const float BALL_RADIUS = 100.0f;
	const float BALL_ANGLE = 0.0f;
	const float ACCELERATION = 20000;
	const unsigned int BALL_SEGMENTS = 64;
};

Player::Player(GameScene* scene) : GameObject(scene) {
	setupGraphics();
	setupPhysics();
	startKeyboardListener();
}

void Player::setupGraphics() {
	DrawNode* graphics = DrawNode::create();
	graphics->drawCircle(Vec2::ZERO, BALL_RADIUS, BALL_ANGLE, BALL_SEGMENTS, true, Color4F(Color3B::ORANGE));
	this->getGameWorld()->addChild(graphics);
	this->graphics = graphics;
}

void Player::setupPhysics() {
	b2Body* body;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(60, 50);
	bodyDef.userData = this;
	body = this->getGameWorld()->getPhysics()->CreateBody(&bodyDef);

	b2CircleShape shape;
	shape.m_radius = 5.0f;
	shape.m_p.Set(0.0f, 0.0f);

	b2FixtureDef shapeDef;
	shapeDef.shape = &shape;
	shapeDef.density = 10.0f;
	shapeDef.friction = 0.4f;
	shapeDef.restitution = 1.0f;

	body->CreateFixture(&shapeDef);
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
	/*
	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = CC_CALLBACK_2(Player::keyPressed, this);
	eventListener->onKeyReleased = CC_CALLBACK_2(Player::keyReleased, this);

	this->getGameWorld()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
	*/
}
