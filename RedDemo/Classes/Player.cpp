#include "Player.h"
#include "GameScene.h"
#include <Box2D\Box2D.h>

USING_NS_CC;

namespace {
	const float BALL_RADIUS = 1.0f;
	const float BALL_ANGLE = 0.0f;
	const float ACCELERATION = 5000;
	const unsigned int BALL_SEGMENTS = 64;
};

Player::Player(GameScene* scene) : GameObject(scene) {
	setupGraphics();
	setupPhysics();
	startKeyboardListener();
}

void Player::setupGraphics() {
	DrawNode* graphics = DrawNode::create();
	graphics->drawCircle(Vec2::ZERO, BALL_RADIUS * RATIO, BALL_ANGLE, BALL_SEGMENTS, true, Color4F(Color3B::ORANGE));
	this->getGameWorld()->addChild(graphics);
	this->graphics = graphics;
}

void Player::setupPhysics() {
	b2Body* body;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(8.6f, 8.0f);
	bodyDef.userData = this;
	body = this->getGameWorld()->getPhysics()->CreateBody(&bodyDef);

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
	b2Body* body = this->getPhysicsBody();

	switch (keyCode){
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
		//body->SetLinearVelocity(b2Vec2(-10, 0));
		body->ApplyForce(b2Vec2(-ACCELERATION ,0), body->GetWorldCenter(), true);
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
		//body->SetLinearVelocity(b2Vec2(10, 0));
		body->ApplyForce(b2Vec2(ACCELERATION ,0), body->GetWorldCenter(), true);
		//body->ApplyForce(b2Vec2(ACCELERATION ,0), body->GetPosition(), true);
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
		//body->SetLinearVelocity(b2Vec2(0,10));
		body->ApplyForce(b2Vec2(0, ACCELERATION), body->GetWorldCenter(), true);
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_S:
		//body->SetLinearVelocity(b2Vec2(0,-10));
		body->ApplyForce(b2Vec2(0, -ACCELERATION), body->GetWorldCenter(), true);
		break;
	}
}

void Player::keyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	b2Body* body = this->getPhysicsBody();
	//body->SetLinearVelocity(b2Vec2(0,0));
	switch (keyCode){
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
		//body->ApplyForce(b2Vec2(ACCELERATION ,0), body->GetWorldCenter(), true);
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
		//body->ApplyForce(b2Vec2(-ACCELERATION ,0), body->GetWorldCenter(), true);
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
		//body->ApplyForce(b2Vec2(0, -ACCELERATION), body->GetWorldCenter(), true);
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_S:
		//body->ApplyForce(b2Vec2(0, ACCELERATION), body->GetWorldCenter(), true);
		break;
	}
}

void Player::startKeyboardListener() {
	
	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = CC_CALLBACK_2(Player::keyPressed, this);
	eventListener->onKeyReleased = CC_CALLBACK_2(Player::keyReleased, this);

	this->getGameWorld()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this->graphics);
	
}
