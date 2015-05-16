#include "MenuScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	this->initMenu();

    return true;
}

void MenuScene::startGameCallback(Ref* pSender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}

void MenuScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
	#endif
}

void MenuScene::initMenu() {

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto menu = Menu::create();
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	// Close button.
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MenuScene::menuCloseCallback, this));

	closeItem->setPosition(
		Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
			 origin.y + closeItem->getContentSize().height / 2));
	menu->addChild(closeItem);

	// Start game button.
	auto startGameButton = MenuItemImage::create(
		"HelloWorld.png",
		"HelloWorld.png",
		CC_CALLBACK_1(MenuScene::startGameCallback, this));

	startGameButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	menu->addChild(startGameButton);
}