#include "FireBallSystem.h"

FireBallSystem::FireBallSystem() {

}

FireBallSystem::~FireBallSystem() {

}


void FireBallSystem::Update(float dt) {

	auto& entities = EntityManager::GetInstance().entities;

	for (auto it = entities.begin(); it != entities.end(); ++it) {

		if (it->second->entity_type != "spell") {

			continue;
		}

		auto tc = it->second->GetComponent<TransformComponent>();
		auto sc = it->second->GetComponent<SpriteComponent>();
		auto fc = it->second->GetComponent<FireBallComponent>();
		
		if (fc) {
			
			if (it->second->has_collided) {
				
				if (!fc->clock_started) {
					fc->clock.restart();
					fc->clock_started = true;
				}

				if (fc->clock.getElapsedTime().asSeconds() > 1.f) {
					EntityManager::GetInstance().entities_to_remove.push_back(it->second);
					it->second->has_collided = false;
					fc->clock_started = false;
				}
				else {
					sc->PlayFrame(0, 0 * 64, 10, 20);
				}

			}
			else {
				tc->position.x += fc->speed * std::cos(fc->angle);
				tc->position.y += fc->speed * std::sin(fc->angle);
				sc->PlayFrame(0, 1 * 64, 100, 45);
			}

			if (fc->clock.getElapsedTime().asSeconds() > 5.f) {
				EntityManager::GetInstance().entities_to_remove.push_back(it->second);
				fc->clock.restart();
			}

		}



	}


}








