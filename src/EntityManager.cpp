#include "../include/EntityManager.h"


EntityManager::EntityManager() { }

EntityManager::~EntityManager() { }

std::shared_ptr<Entity> EntityManager::CreateEntity(std::string name) {
	
	std::shared_ptr<Entity> new_entity = std::make_shared<Entity>();

	entities.insert(std::make_pair(name, new_entity));

	return new_entity;
}

std::shared_ptr<Entity> EntityManager::GetEntity(std::string name) {
	return entities[name];
}

std::shared_ptr<Entity> EntityManager::CreateMapEntity(std::string name) {

	if (levels.find(name) == levels.end()) {
		levels[name] = std::vector<std::shared_ptr<Entity>>();
	}

	std::shared_ptr<Entity> new_entity = std::make_shared<Entity>();

	levels.at(name).emplace_back(new_entity);

	return new_entity;

}

std::vector<std::shared_ptr<Entity>> EntityManager::GetMapEntity(std::string name) {
	return levels.at(name);
}

std::shared_ptr<Entity> EntityManager::CreateEnemyEntity(std::string name) {
	
	if (enemies.find(name) == enemies.end()) {
		enemies[name] = std::vector<std::shared_ptr<Entity>>();
	}

	std::shared_ptr<Entity> new_entity = std::make_shared<Entity>();

	enemies.at(name).emplace_back(new_entity);

	return new_entity;
}

std::vector<std::shared_ptr<Entity>> EntityManager::GetEnemyEntity(std::string name) {
	return enemies.at(name);
}


void EntityManager::UpdateAll(float dt) {

	for (const auto& entity : entities_to_remove) {
		auto it = std::find_if(entities.begin(), entities.end(), [&](const auto& pair) {
			return pair.second == entity;
			});
		if (it != entities.end()) {
			std::cout << "Entity: " << it->second->entity_type << " removed " << std::endl;
			entities.erase(it);
			std::cout << "size after removing: " << entities.size() << std::endl;
		}
	}

	for (const auto& entity : entities_to_remove) {
		auto it = std::find_if(levels[current_level].begin(), levels[current_level].end(), [&](const auto& pair) {
			return pair == entity;
			});
		if (it != levels[current_level].end()) {
			std::cout << "Entity: " <<  (*it)->entity_type<< " removed " << std::endl;
			levels[current_level].erase(it);
			std::cout << "size after removing: " << levels[current_level].size() << std::endl;
		}
	}

}


void EntityManager::RenderLevel(sf::RenderWindow& window, std::string level_name, sf::View view) {

	if (levels.find(level_name) != levels.end()) {

		for (const auto& entity : levels.at(level_name)) {

			auto tc = entity->GetComponent<TransformComponent>();
			auto sc = entity->GetComponent<SpriteComponent>();

			if (entity->GetComponent<SpriteComponent>()->is_renderable) {
				// render map entities only if they are in view, no need to have everything render always
				if (tc->position.x + 500 >= view.getCenter().x - view.getSize().x / 2 &&
					tc->position.x - 500 <= view.getCenter().x + view.getSize().x / 2 &&
					tc->position.y + 500 >= view.getCenter().y - view.getSize().y / 2 &&
					tc->position.y - 500 <= view.getCenter().y + view.getSize().y / 2)
				{

					sc->sprite.setPosition(tc->position);
					sc->sprite.setRotation(tc->rotation);
					sc->sprite.setScale(tc->scale);

					entity->render(window);

				}

			}

		}

	}

}

void EntityManager::RenderPlayer(sf::RenderWindow& window, sf::View view) {

	//auto player = GetEntity("player");

	//if (player) {
	//	auto tc = player->GetComponent<TransformComponent>();
	//	auto sc = player->GetComponent<SpriteComponent>();

	//	sc->sprite.setPosition(tc->position);
	//	sc->sprite.setRotation(tc->rotation);
	//	sc->sprite.setScale(tc->scale);

	//	player->render(window);
	//}

	for (auto it = entities.begin(); it != entities.end(); ++it) {
		
		auto tc = it->second->GetComponent<TransformComponent>();
		auto sc = it->second->GetComponent<SpriteComponent>();

		if (tc && sc) {
			sc->sprite.setPosition(tc->position);
			sc->sprite.setRotation(tc->rotation);
			sc->sprite.setScale(tc->scale);

			if (it->second->entity_type != "player") {
				// render things beside player only if they are in view, no need to render all the time
				if (tc->position.x + 1000 >= view.getCenter().x - view.getSize().x / 2 &&
					tc->position.x - 1000 <= view.getCenter().x + view.getSize().x / 2 &&
					tc->position.y + 1000 >= view.getCenter().y - view.getSize().y / 2 &&
					tc->position.y - 1000 <= view.getCenter().y + view.getSize().y / 2)
				{

					it->second->render(window);

				}

			}
			else {
				it->second->render(window);
			}


			
		}

	}


}

void EntityManager::RenderEnemies(sf::RenderWindow& window, std::string level_name, sf::View view) {

	if (enemies.find(level_name) != enemies.end()) {

		for (const auto& enemy : enemies.at(level_name)) {

			//sf::Vector2f entity_pos = enemy->GetComponent<TransformComponent>()->position;

			auto tc = enemy->GetComponent<TransformComponent>();
			auto sc = enemy->GetComponent<SpriteComponent>();

			if (enemy->GetComponent<SpriteComponent>()->is_renderable) {
				// render enemies only if they are in view, no need to render all the time
				if (tc->position.x + 1000 >= view.getCenter().x - view.getSize().x / 2 &&
					tc->position.x - 1000 <= view.getCenter().x + view.getSize().x / 2 &&
					tc->position.y + 1000 >= view.getCenter().y - view.getSize().y / 2 &&
					tc->position.y - 1000 <= view.getCenter().y + view.getSize().y / 2)
				{

					sc->sprite.setPosition(tc->position);
					sc->sprite.setRotation(tc->rotation);
					sc->sprite.setScale(tc->scale);

					enemy->render(window);

				}

			}


		}
	}

}
