#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <../include/json.hpp>

#include "EntityManager.h"

using json = nlohmann::json;

class LevelMap {

	public:

		LevelMap();
		~LevelMap();

		void reload_map();


	private:

		const int SPRITE_SIZE = 32;

};


