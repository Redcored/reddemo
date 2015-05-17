#pragma once
#include "GameObject.h"

class Platform : public GameObject {

public:
	Platform(GameScene* scene);

private:
	void setupGraphics();
	void setupPhysics();

};