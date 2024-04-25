#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>
#include <vector>

#include "Entity.h"
//#include "Camera.h"
//#include "Collision.h"

class EntityManager {

	public:

		static EntityManager& GetInstance() {
			static EntityManager* instance = new EntityManager;
			return *instance;
		}

		std::shared_ptr<Entity> CreateEntity(std::string name);
		std::shared_ptr<Entity> GetEntity(std::string name);


		std::shared_ptr<Entity> CreateMapEntity(std::string name);
		std::vector<std::shared_ptr<Entity>> GetMapEntity(std::string name);
		
		std::shared_ptr<Entity> CreateEnemyEntity(std::string name);
		std::vector<std::shared_ptr<Entity>> GetEnemyEntity(std::string name);


		void UpdateAll(float dt);
		
		void RenderLevel(sf::RenderWindow& window, std::string level_name, sf::View view);
		void RenderPlayer(sf::RenderWindow& window, sf::View view);
		void RenderEnemies(sf::RenderWindow& window, std::string level_name, sf::View view);

		std::unordered_map<std::string, std::shared_ptr<Entity>> entities;
		std::unordered_map<std::string, std::vector<std::shared_ptr<Entity>>> levels;
		std::unordered_map<std::string, std::vector<std::shared_ptr<Entity>>> enemies;

		std::vector<std::shared_ptr<Entity>> entities_to_remove;

		std::string current_level = "level1";

	private:

		EntityManager();
		~EntityManager();

		
};