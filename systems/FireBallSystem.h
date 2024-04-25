#pragma once

#include <iostream>
#include <math.h>

#include "SFML/Graphics.hpp"

#include "System.h"
#include "../include/EntityManager.h"

class FireBallSystem : public System {

	public:

		FireBallSystem();
		~FireBallSystem();

		void Update(float dt) override;

		

};