#pragma once

#include <iostream>
#include <string>

#include "SFML/Graphics.hpp"

#include "IComponent.h"


class SkeletonEnemyComponent : public Component {

	public:

		SkeletonEnemyComponent();
		~SkeletonEnemyComponent();

		float attack_range;
		float follow_range;
		float inplace_range;

		bool follow_forever;
		bool is_attackable;
		bool is_attacked;

		sf::Clock clock;
		bool clock_started;


};