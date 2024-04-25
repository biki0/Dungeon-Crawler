#include "AnimationSystem.h"

AnimationSystem::AnimationSystem() {

}

AnimationSystem::~AnimationSystem() {

}


void AnimationSystem::Update(float dt) {

	auto& levels_ent = EntityManager::GetInstance().levels;
	auto& entities_enemy = EntityManager::GetInstance().enemies;

	if (levels_ent.find(EntityManager::GetInstance().current_level) != levels_ent.end()) {

		for (const auto& entity : levels_ent.at(EntityManager::GetInstance().current_level)) {

			auto sc = entity->GetComponent<SpriteComponent>();

			if (!sc->has_animation) {
				continue;
			}

			if (entity->entity_type == "COLLECTABLE") {
				sc->PlayFrame(0, 0 * 32, 200, 4);
			}

			//if (entity->entity_type == "skeleton") {
			//	sc->PlayFrame(0, 0 * 64, 100, 12);
			//}

			if (entity->entity_type == "torch") {
				sc->PlayFrame(0, 0 * 64, 100, 4);
				sc->PlayFrame(0, 1 * 64, 100, 4);
			}

		}

	}

}









