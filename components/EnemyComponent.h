#pragma once

#include <iostream>
#include <string>

#include "SFML/Graphics.hpp"

#include "IComponent.h"

class EnemyComponent : public Component {

	public:

		EnemyComponent();
		~EnemyComponent();

	
		bool is_attackable;
		bool is_hit;
		bool attack_player;


};