#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

#include <SFML/Graphics.hpp>

#include "EntityManager.h"
#include "../systems/SystemManager.h"

#include "../include/Camera.h"
#include "../include/Player.h"
#include "../include/LevelMap.h"

class Game {

	public:
		
		Game();
		~Game();

		void run();

	private:

		void update();
		void render();


	private:

		Camera m_camera;
		Player m_player;
		LevelMap m_level_map;

	private:

		sf::RenderWindow m_window;
		sf::Event m_event;
		sf::Clock m_clock;

};
