#include "SystemManager.h"


SystemManager::SystemManager() {



}

SystemManager::~SystemManager() {

}


void SystemManager::Update(float dt) {


	for (auto system : systems) {

		system->Update(dt);

	}

}












