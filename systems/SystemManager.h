#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>
#include <vector>

#include "PhysicsSystem.h"
//#include "SpriteSystem.h"
#include "CollisionSystem.h"
#include "AnimationSystem.h"
#include "FireBallSystem.h"
#include "SkeletonEnemySystem.h"

class SystemManager {

	public:

		static SystemManager& GetInstance() {
			static SystemManager* instance = new SystemManager;
			return *instance;
		}




		template<typename T, typename... Args>
		std::shared_ptr<T> AddSystem(Args&&... args) {
			std::shared_ptr<T> system = std::make_shared<T>(std::forward<Args>(args)...);
			systems.emplace_back(system);
			return system;
		}


		void Update(float dt);

	private:

		SystemManager();
		~SystemManager();
		std::vector<std::shared_ptr<System>> systems;


};