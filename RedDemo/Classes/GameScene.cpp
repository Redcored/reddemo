#include "GameScene.h"
#include "PauseMenu.h"
#include "Platform.h"
#include "Player.h"
#include "GameObject.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	// Setting up the scene
	auto scene = Scene::createWithPhysics();

	auto layer = GameScene::create();
	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	// Super init handling
	if (!Layer::init()) { return false; }

	initMenu();
	setupPhysics();
	
	gameObjects.push_back(new Platform(this, Size(1000.0f, 1.0f), Vec2(0.0f, 0.0f)));
	gameObjects.push_back(new Player(this));

	this->runAction(Follow::create(gameObjects.at(1)->getGraphics()));

	this->scheduleUpdate();
	return true;
}

b2World* GameScene::getPhysics() {
	return this->physicsWorld;
}

void GameScene::update(float deltaTime) {

	// Currently, there is nothing to do
	this->physicsWorld->Step(deltaTime, 8, 3);
	for (b2Body* b = this->physicsWorld->GetBodyList();
		b; b = b->GetNext()) {
		//log("Speed: %f", b->GetLinearVelocity());
		log("Y: %f, X: %f, angle: %f, angular velocity: %f", b->GetPosition().y, b->GetPosition().x, -b->GetAngle()/3.14*180, b->GetAngularVelocity());
	}

	for (GameObject* o : gameObjects) {
		o->update();
	}

}

void GameScene::initMenu() {

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto menu = Menu::create();
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	// Close button.
	auto resumeButton = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameScene::pauseCallback, this));

	resumeButton->setPosition(
		Vec2(origin.x + visibleSize.width - resumeButton->getContentSize().width / 2,
		origin.y + resumeButton->getContentSize().height / 2));
	menu->addChild(resumeButton);

	// Paused text
	label = Label::createWithTTF("GAME IS PLAYING", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

}

void GameScene::pauseCallback(Ref* pSender) {
	auto scene = PauseMenu::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(0.25, scene));
}

void GameScene::setupPhysics() {
	this->physicsWorld = new b2World(b2Vec2(0, -9.81));
}