#include "GameScene.h"
#include "PauseMenu.h"
#include "Platform.h"
#include "Player.h"

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
	
	GameObject* plat = new Platform(this);
	//plat->setPosition(1920 / 2, 100);

	Player* player = new Player(this);
	//player->setPosition(1920 / 2, 400);

	//this->runAction(Follow::create(player));

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
		log("Speed: %f", b->GetLinearVelocity());
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