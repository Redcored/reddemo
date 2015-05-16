#include "PauseMenu.h"
#include "GameScene.h"

USING_NS_CC;

Scene* PauseMenu::createScene()
{
	// Setting up the scene
	auto scene = Scene::create();
	auto layer = PauseMenu::create();
	scene->addChild(layer);

	return scene;
}

bool PauseMenu::init()
{
	// Super init handling
	if (!Layer::init()) { return false; }

	initMenu();

	return true;
}

void PauseMenu::initMenu() {

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto menu = Menu::create();
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	// Close button.
	auto resumeButton = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(PauseMenu::resumeCallback, this));

	resumeButton->setPosition(
		Vec2(origin.x + visibleSize.width - resumeButton->getContentSize().width / 2,
		origin.y + resumeButton->getContentSize().height / 2));
	menu->addChild(resumeButton);

	// Paused text
	auto label = Label::createWithTTF("Paused", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);
}

void PauseMenu::resumeCallback(Ref* pSender) {
	//auto scene = GameScene::createScene();
	Director::getInstance()->popScene();
}