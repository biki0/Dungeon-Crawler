#include "CollisionSystem.h"

CollisionSystem::CollisionSystem() {

}

CollisionSystem::~CollisionSystem() {

}

void CollisionSystem::Update(float dt) {

    auto& entities = EntityManager::GetInstance().entities;
    auto& entities_map = EntityManager::GetInstance().levels;
    auto& entities_enemy = EntityManager::GetInstance().enemies;
    auto& currentLevel = EntityManager::GetInstance().current_level;

    auto player = EntityManager::GetInstance().GetEntity("player");
    auto player_sprite = player->GetComponent<SpriteComponent>()->sprite;
    auto player_bounds = player_sprite.getGlobalBounds();

    for (auto& entity : entities_map[currentLevel]) {
        if (!entity->is_collidable) {
            continue;
        }

        auto entity_sprite = entity->GetComponent<SpriteComponent>()->sprite;
        auto entity_bounds = entity_sprite.getGlobalBounds();

        if (!player_bounds.intersects(entity_bounds)) {
            continue; 
        }

        if (Collision::pixelPerfectTest(player_sprite, entity_sprite)) {
            if (entity->entity_type == "COLLECTABLE") {
                std::cout << "COIN" << std::endl;
                EntityManager::GetInstance().entities_to_remove.push_back(entity);
            }
            else {
                HandleCollision(player, entity, dt);
            }
        }
    }

    for (auto& enemy : entities_enemy[currentLevel]) {

        for (auto it = entities.begin(); it != entities.end(); ++it) {

            auto entity = it->second;

            if (entity->entity_type == "spell" && !entity->has_collided) { //enemy collision with spells
                
                if (Collision::pixelPerfectTest(enemy->GetComponent<SpriteComponent>()->sprite, entity->GetComponent<SpriteComponent>()->sprite) 
                    && enemy->GetComponent<EnemyComponent>()->is_attackable) {
                    entity->has_collided = true;
                    enemy->has_collided = true;
                    enemy->GetComponent<EnemyComponent>()->is_hit = true;
                }

            }

            if (entity->entity_type == "player") { //player enemy collision
                if (Collision::pixelPerfectTest(enemy->GetComponent<SpriteComponent>()->sprite, entity->GetComponent<SpriteComponent>()->sprite)) {
                    entity->has_collided = true;
                    enemy->GetComponent<EnemyComponent>()->attack_player = true;
                    std::cout << "PLAYER HIT ENEMY" << std::endl;
                }
            }


        }

    }

    
    //for (const auto& entity : entities_to_remove) {
    //    auto it = std::find(entities_map[currentLevel].begin(), entities_map[currentLevel].end(), entity);
    //    if (it != entities_map[currentLevel].end()) {
    //        entities_map[currentLevel].erase(it);
    //    }
    //}

}


void CollisionSystem::HandleCollision(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity> entity2, float dt) {

    auto tc = entity1->GetComponent<TransformComponent>();
    auto rb = entity1->GetComponent<RigidBodyComponent>();
    auto p_sprite = entity1->GetComponent<SpriteComponent>()->sprite;
    auto t_sprite = entity2->GetComponent<SpriteComponent>()->sprite;

    auto etc = entity2->GetComponent<TransformComponent>();

    if (rb) {

        sf::FloatRect intersection;
        if (p_sprite.getGlobalBounds().intersects(t_sprite.getGlobalBounds(), intersection)) {
            if (intersection.width < intersection.height) {
                if (tc->position.x < etc->position.x) {
                    
                    rb->velocity.x = 0.0f;
                    rb->ApplyForce(-9.0f, 0);
                   
                   

                }

                else if (tc->position.x > etc->position.x) {
                    
                    rb->velocity.x = 0.0f;
                    rb->ApplyForce(9.0f, 0);
   
                }

            }
            else {

                if (tc->position.y < etc->position.y) {
                    
                    rb->velocity.y = 0.0f;
                    rb->ApplyForce(0, -7.0f);

                }
                else if(tc->position.y > etc->position.y) {
                    
                    rb->velocity.y = 0.0f;
                    rb->ApplyForce(0, 7.0f);

                }

            }
        
        }
    }
    
}








