#pragma once
#include "GameObject.h"

class Platform :
	public GameObject {
public:
	Platform(cocos2d::Layer* layer);
protected:
	virtual void addToLayer(cocos2d::Layer* layer) const override;
private:
	void setupGraphics();
	cocos2d::DrawNode* graphics;
};