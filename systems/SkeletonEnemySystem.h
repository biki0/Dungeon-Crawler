#pragma once

#include <iostream>
#include <math.h>

#include "SFML/Graphics.hpp"

#include "System.h"
#include "../include/EntityManager.h"

class SkeletonEnemySystem : public System {

public:

	SkeletonEnemySystem();
	~SkeletonEnemySystem();

	void Update(float dt) override;

	int sprite_dir;

};