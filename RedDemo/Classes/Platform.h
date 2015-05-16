#pragma once
#include "GameObject.h"

class Platform : public GameObject {

public:
	Platform();

private:
	void setupGraphics();
	void setupPhysics();

};