#include "Player.h"

#include <Box2D\Box2D.h>
#include "GameWorld.h"

USING_NS_CC;

namespace {
	const float BALL_RADIUS = 1.0f;
	const float BALL_ANGLE = 0.0f;
	const float HORIZONTAL_ACCELERATION = 16000;
	const float VERTICAL_ACCELERATION = 12000;
	const unsigned int BALL_SEGMENTS = 64;
};

Player::Player(GameWorld& world) : GameObject(world), forceVector(0,0) {
	setupGraphics();
	setupPhysics();

	this->oldPosition = Vec2(this->getPhysicsBody()->GetPosition().x, this->getPhysicsBody()->GetPosition().y);
	this->newPosition = this->oldPosition;

	startKeyboardListener();
}

void Player::physicsTick(float physicsTickLength) {
	auto body = this->getPhysicsBody();
	body->ApplyForce(b2Vec2(forceVector.x*physicsTickLength,forceVector.y*physicsTickLength), body->GetWorldCenter(), true);
	GameObject::physicsTick(physicsTickLength);
}

void Player::setupGraphics() {
	DrawNode* graphics = DrawNode::create();
	graphics->drawCircle(Vec2::ZERO, BALL_RADIUS * RATIO, BALL_ANGLE, BALL_SEGMENTS, true, Color4F(Color3B::ORANGE));
	this->graphics = graphics;
}

void Player::setupPhysics() {
	b2Body* body;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(8.6f, 8.0f);
	bodyDef.userData = this;
	body = this->getGameWorld().getPhysics()->CreateBody(&bodyDef);

	b2CircleShape shape;
	shape.m_radius = BALL_RADIUS;
	shape.m_p.Set(0.0f, 0.0f);

	b2FixtureDef shapeDef;
	shapeDef.shape = &shape;
	shapeDef.density = 10.0f;
	shapeDef.friction = 0.8f;
	shapeDef.restitution = 0.8f;

	body->CreateFixture(&shapeDef);
	this->setPhysicsBody(body);
}

void Player::keyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	switch (keyCode){
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
		forceVector.add(Vec2(-HORIZONTAL_ACCELERATION, 0));
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
		forceVector.add(Vec2(HORIZONTAL_ACCELERATION, 0));
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
		forceVector.add(Vec2(0, VERTICAL_ACCELERATION));
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_S:
		forceVector.add(Vec2(0, -VERTICAL_ACCELERATION));
		break;
	}
}

void Player::keyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	switch (keyCode){
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
		forceVector.add(Vec2(HORIZONTAL_ACCELERATION, 0));
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
		forceVector.add(Vec2(-HORIZONTAL_ACCELERATION, 0));
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
		forceVector.add(Vec2(0, -VERTICAL_ACCELERATION));
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_S:
		forceVector.add(Vec2(0, VERTICAL_ACCELERATION));
		break;
	}
}

void Player::startKeyboardListener() {
	
	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = CC_CALLBACK_2(Player::keyPressed, this);
	eventListener->onKeyReleased = CC_CALLBACK_2(Player::keyReleased, this);
	this->getGraphics()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this->graphics);
}
