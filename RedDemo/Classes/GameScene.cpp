#include "GameScene.h"
#include "PauseMenu.h"
#include "Platform.h"
#include "Player.h"
#include "GameObject.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	// Setting up the scene
	auto scene = Scene::create();
	//auto scene = Scene::createWithPhysics();

	auto layer = GameScene::create();
	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	// Super init handling
	if (!Layer::init()) { return false; }

	accumulator = 0;

	initMenu();
	setupPhysics();

	gameObjects.push_back(new Player(this));
	for (int i = 0; i < 500; i++) {
		float rand = random(0, 10);
		if (rand < 1) {}
		else if (rand < 6) {
			gameObjects.push_back(new Platform(this, Size(10.0f, 1.0f), Vec2((float)10.0f * i, 10.8)));
			gameObjects.push_back(new Platform(this, Size(10.0f, 1.0f), Vec2((float)10.0f * i, 0)));
		}
		else if (rand < 8) {
			gameObjects.push_back(new Platform(this, Size(10.0f, 1.0f), Vec2((float)10.0f * i, 10.8)));
		}
		else {
			gameObjects.push_back(new Platform(this, Size(10.0f, 1.0f), Vec2((float)10.0f * i, 0)));
		}

	}

	this->runAction(Follow::create(gameObjects.at(0)->getGraphics()));

	this->scheduleUpdate();
	return true;
}

b2World* GameScene::getPhysics() {
	return this->physicsWorld;
}

void GameScene::update(float deltaTime) {

	this->accumulator += deltaTime;

	float physicsTick = 0.03;
	while (this->accumulator >= physicsTick) {

		this->physicsWorld->Step(physicsTick, 8, 3);
		for (GameObject* o : gameObjects) {
			o->updatePhysics(physicsTick);
		}

		this->accumulator -= physicsTick;
	}

	gameObjects.at(0)->updateGraphics(this->accumulator);

	float zoom = 1;
	this->setPosition(- (gameObjects.at(0)->getGraphics()->getPosition().x - 500)*zoom, this->getPosition().y);
	this->setScale(zoom);
	//gameObjects.at(0)->getGraphics()->setPosition(0, 0);
	/*
	for (GameObject* o : gameObjects) {
		o->getGraphics()->setPosition(o->getGraphics()->getPosition() - gameObjects.at(0)->getGraphics()->getPosition() + Vec2(500, 500));
	}
	*/
	//gameObjects.at(0)->update(this->accumulator/physicsTick);

	/*
	for (b2Body* b = this->physicsWorld->GetBodyList();
		b; b = b->GetNext()) {
	}

	for (GameObject* o : gameObjects) {
		o->update();
	}
	*/

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