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

			auto skeleton = enemy->GetComponent<SkeletonEnemyComponent>();
			auto enemy_c = enemy->GetComponent<EnemyComponent>();

			if (skeleton && enemy->entity_type == "skeleton") {

				auto etc = enemy->GetComponent<TransformComponent>();
				auto erb = enemy->GetComponent<RigidBodyComponent>();
				auto esp = enemy->GetComponent<SpriteComponent>();

				sf::Vector2f direction = player_position->position - etc->position;
				float player_distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
				if (!enemy_c->is_hit) {
					if (player_distance < skeleton->attack_range) {

						esp->PlayFrame(0, 0 * 64, 100, 12);

						if (skeleton->is_attackable) {

							std::shared_ptr<TransformComponent> tc = player->GetComponent<TransformComponent>();
							std::shared_ptr<RigidBodyComponent> rb = player->GetComponent<RigidBodyComponent>();

							sf::Sprite p_sprite = player->GetComponent<SpriteComponent>()->sprite;
							sf::Sprite t_sprite = enemy->GetComponent<SpriteComponent>()->sprite;

							std::shared_ptr<TransformComponent> e_tc = enemy->GetComponent<TransformComponent>();
							if (enemy_c->attack_player = true) {
								esp->PlayFrame(0, 0 * 64, 100, 12);
								enemy_c->attack_player = false;

							}

						}

					}
					else if (player_distance < skeleton->follow_range || skeleton->follow_forever) {

						if (player_distance > 0.001f) {
							direction /= player_distance;
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
						skeleton->follow_forever = true;
						esp->PlayFrame(0, 2 * 64, 150, 12);

					}
					else {

						esp->PlayFrame(0, 2 * 64, 150, 12);
						erb->ApplyForce(2 * sprite_dir, 0);

						if (etc->position.x < etc->original_pos.x - skeleton->inplace_range) {

							sprite_dir = 1;
							esp->sprite.setOrigin({ 0, 0 });
							etc->scale = { 1, 1 };

						}
						if (etc->position.x > etc->original_pos.x + skeleton->inplace_range) {

							sprite_dir = -1;
							esp->sprite.setOrigin({ esp->sprite.getLocalBounds().width, 0 });
							etc->scale = { -1, 1 };
						}

					}
				}
				else {
					skeleton->follow_forever = true; //if player spell hits skeleton then skeleton should instantly go attack player
					erb->velocity = { 0,0 };
					std::shared_ptr<TransformComponent> tc = player->GetComponent<TransformComponent>();
					std::shared_ptr<RigidBodyComponent> rb = player->GetComponent<RigidBodyComponent>();

					sf::Sprite p_sprite = player->GetComponent<SpriteComponent>()->sprite;
					sf::Sprite t_sprite = enemy->GetComponent<SpriteComponent>()->sprite;

					std::shared_ptr<TransformComponent> e_tc = enemy->GetComponent<TransformComponent>();
					if (enemy_c->is_hit) {
						if (!skeleton->clock_started) {
							skeleton->clock.restart();
							skeleton->clock_started = true;
						}
						if (skeleton->clock.getElapsedTime().asSeconds() > 1.f) {
							//enemy->has_collided = false;
							skeleton->clock_started = false;
							enemy_c->is_hit = false;
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









