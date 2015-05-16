#pragma once

#include "cocos2d.h"

class PauseMenu : public cocos2d::Layer
{
public:

	// Cocos 2D's management functions.
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(PauseMenu);

private:
	
	void initMenu();
	void resumeCallback(Ref* pSender);

};

