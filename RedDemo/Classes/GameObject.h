#pragma once

#include "cocos2d.h"

class GameObject {
protected:
	virtual void addToLayer(cocos2d::Layer* layer) const = 0;
};