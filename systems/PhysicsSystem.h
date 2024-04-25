#pragma once

#include <iostream>

#include "SFML/Graphics.hpp"

#include "System.h"
#include "../include/EntityManager.h"


class PhysicsSystem : public System {

	public:

		PhysicsSystem();
		~PhysicsSystem();

		void Update(float dt) override;



};