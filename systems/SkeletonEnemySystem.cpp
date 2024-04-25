#include "SkeletonEnemySystem.h"

SkeletonEnemySystem::SkeletonEnemySystem(){
	sprite_dir = 1;
}

SkeletonEnemySystem::~SkeletonEnemySystem() {

}


void SkeletonEnemySystem::Update(float dt) {

	auto& enemies = EntityManager::GetInstance().enemies;

	std::shared_ptr<Entity> player = EntityManager::GetInstance().GetEntity("player");
	auto player_position = player->GetComponent<TransformComponent>();
	
	if (enemies.find(EntityManager::GetInstance().current_level) != enemies.end()) {

		for (const auto& enemy : enemies.at(EntityManager::GetInstance().current_level)) {

			auto esc = enemy->GetComponent<SkeletonEnemyComponent>();

			if (esc && enemy->entity_type == "skeleton") {

				auto etc = enemy->GetComponent<TransformComponent>();
				auto erb = enemy->GetComponent<RigidBodyComponent>();
				auto esp = enemy->GetComponent<SpriteComponent>();

				sf::Vector2f direction = player_position->position - etc->position;
				float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
				if (!esc->is_attacked) {
					if (distance < esc->attack_range) {

						esp->PlayFrame(0, 0 * 64, 100, 12);

						if (esc->is_attackable) {

							std::shared_ptr<TransformComponent> tc = player->GetComponent<TransformComponent>();
							std::shared_ptr<RigidBodyComponent> rb = player->GetComponent<RigidBodyComponent>();

							sf::Sprite p_sprite = player->GetComponent<SpriteComponent>()->sprite;
							sf::Sprite t_sprite = enemy->GetComponent<SpriteComponent>()->sprite;

							std::shared_ptr<TransformComponent> e_tc = enemy->GetComponent<TransformComponent>();
							if (enemy->has_collided) {

								esp->PlayFrame(0, 0 * 64, 100, 12);


							}

						}

					}
					else if (distance < esc->follow_range || esc->follow_forever) {

						if (distance > 0.001f) {
							direction /= distance;
						}

						if (direction.x < 0) {

							esp->sprite.setOrigin({ esp->sprite.getLocalBounds().width, 0 });
							etc->scale = { -1, 1 };

						}
						else {

							esp->sprite.setOrigin({ 0, 0 });
							etc->scale = { 1, 1 };

						}

						erb->ApplyForce(7 * direction.x, 7 * direction.y);
						esc->follow_forever = true;
						esp->PlayFrame(0, 2 * 64, 150, 12);

					}
					else {

						esp->PlayFrame(0, 2 * 64, 150, 12);
						erb->ApplyForce(2 * sprite_dir, 0);

						if (etc->position.x < etc->original_pos.x - esc->inplace_range) {

							sprite_dir = 1;
							esp->sprite.setOrigin({ 0, 0 });
							etc->scale = { 1, 1 };

						}
						if (etc->position.x > etc->original_pos.x + esc->inplace_range) {

							sprite_dir = -1;
							esp->sprite.setOrigin({ esp->sprite.getLocalBounds().width, 0 });
							etc->scale = { -1, 1 };
						}

					}
				}
				else {
					erb->ApplyForce(0, 0);
					std::shared_ptr<TransformComponent> tc = player->GetComponent<TransformComponent>();
					std::shared_ptr<RigidBodyComponent> rb = player->GetComponent<RigidBodyComponent>();

					sf::Sprite p_sprite = player->GetComponent<SpriteComponent>()->sprite;
					sf::Sprite t_sprite = enemy->GetComponent<SpriteComponent>()->sprite;

					std::shared_ptr<TransformComponent> e_tc = enemy->GetComponent<TransformComponent>();
					if (esc->is_attacked) {
						if (!esc->clock_started) {
							esc->clock.restart();
							esc->clock_started = true;
						}
						if (esc->clock.getElapsedTime().asSeconds() > 1.f) {
							//enemy->has_collided = false;
							esc->clock_started = false;
							esc->is_attacked = false;
						}
						else {
							esp->PlayFrame(0, 4 * 64, 100, 3);
						}
					}

				}


			}

		}

	}

}









