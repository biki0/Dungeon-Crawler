#pragma once

#include <iostream>

#include "SFML/Graphics.hpp"

#include "System.h"
#include "../include/EntityManager.h"

class AnimationSystem : public System {

public:

	AnimationSystem();
	~AnimationSystem();

	void Update(float dt) override;

	sf::Clock clock;
	bool clock_started = false;


};