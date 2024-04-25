#pragma once

#include "SFML/Graphics.hpp"

#include <memory>
#include <unordered_map>
#include <string>

#include "../components/TransformComponent.h"
#include "../components/SpriteComponent.h"
#include "../components/RigidBodyComponent.h"
#include "../components/ColliderComponent.h"
#include "../components/SkeletonEnemyComponent.h"
#include "../components/CoinComponent.h"
#include "../components/FireBallComponent.h"

class Entity {

    public:
        Entity();
        ~Entity();

        template<typename T, typename... Args>
        std::shared_ptr<T> AddComponent(Args&&... args) {
            std::shared_ptr<T> component = std::make_shared<T>(std::forward<Args>(args)...);
            m_components[typeid(T).name()] = component;
            return component;
        }

        template<typename T>
        std::shared_ptr<T> GetComponent() {
            const auto& it = m_components.find(typeid(T).name());
            if (it != m_components.end()) {
                return std::dynamic_pointer_cast<T>(it->second);
            }
            return nullptr;
        }

        template<typename T>
        bool HasComponent() {
            return m_components.find(typeid(T).name()) != m_components.end();
        }


        void update(float dt);
        void render(sf::RenderWindow& window);

        bool is_collidable;
        bool has_collided = false;
        //EntityType entity_type;
        std::string entity_type;

    private:

        std::unordered_map<std::string, std::shared_ptr<Component>> m_components;


};