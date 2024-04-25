#include "../include/LevelMap.h"

sf::IntRect getSpriteRect(int index) {
    int SHEET_WIDTH = 128;
    int SHEET_HEIGHT = 48;
    int SPRITE_WIDTH = 16;
    int SPRITE_HEIGHT = 16;
    int row = index / (SHEET_WIDTH / SPRITE_WIDTH);
    int col = index % (SHEET_WIDTH / SPRITE_WIDTH);
    return sf::IntRect(col * SPRITE_WIDTH, row * SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT);
}


LevelMap::LevelMap() {
    
    std::ifstream file("assets/level_map/level1/map.json");
    if (!file.is_open()) {
        std::cerr << "Failed to open JSON file\n";
    }

    json json_data;
    file >> json_data;

    for (const auto& layer_data : json_data["layers"]) {
        for (const auto& tile_data : layer_data["tiles"]) {

            if (layer_data["name"] == "floor") {

                auto entity = EntityManager::GetInstance().CreateMapEntity("level1");
                entity->is_collidable = layer_data["collider"];
                auto tc = entity->AddComponent<TransformComponent>(tile_data["x"] * SPRITE_SIZE, tile_data["y"] * SPRITE_SIZE);
                auto sc = entity->AddComponent<SpriteComponent>(tc, "assets/level_map/level1/spritesheet.png", SPRITE_SIZE, SPRITE_SIZE);
                std::string id = tile_data["id"];
                sc->SetTextureRect(getSpriteRect(std::stoi(id)));
                tc->scale = { 2, 2 };

            }

        }
    }

    for (const auto& layer_data : json_data["layers"]) { 
        for (const auto& tile_data : layer_data["tiles"]) {
            
            if (layer_data["collider"]) {

                auto entity = EntityManager::GetInstance().CreateMapEntity("level1");
                entity->is_collidable = layer_data["collider"];
                entity->entity_type = layer_data["name"];
                auto tc = entity->AddComponent<TransformComponent>(tile_data["x"] * SPRITE_SIZE, tile_data["y"] * SPRITE_SIZE);
                
                if (layer_data["name"] == "COLLECTABLE") {
                    auto sc = entity->AddComponent<SpriteComponent>(tc, "assets/level_map/level1/coins.png", 16, 16);
                    //entity->AddComponent<CoinComponent>(sc);
                    sc->has_animation = true;
                    tc->scale = { 2, 2 };
                }
                else {
                    auto sc = entity->AddComponent<SpriteComponent>(tc, "assets/level_map/level1/spritesheet.png", SPRITE_SIZE, SPRITE_SIZE);
                    std::string id = tile_data["id"];
                    sc->SetTextureRect(getSpriteRect(std::stoi(id)));
                    tc->scale = { 2, 2 };
                }

            }

        }
    }

    for (const auto& layer_data : json_data["layers"]) {
        for (const auto& tile_data : layer_data["tiles"]) {

            if (layer_data["name"] == "skeleton") {

                auto entity = EntityManager::GetInstance().CreateEnemyEntity("level1");
                entity->is_collidable = layer_data["collider"];
                entity->entity_type = layer_data["name"];
                auto tc = entity->AddComponent<TransformComponent>(tile_data["x"] * SPRITE_SIZE, tile_data["y"] * SPRITE_SIZE);
                auto sc = entity->AddComponent<SpriteComponent>(tc, "assets/level_map/level1/skeleton.png", SPRITE_SIZE*2, SPRITE_SIZE*2);
                auto rb = entity->AddComponent<RigidBodyComponent>(tc);
                entity->AddComponent<SkeletonEnemyComponent>();
                sc->has_animation = true;
                //tc->scale = { 2, 2 };

            }

        }
    }


    for (const auto& layer_data : json_data["layers"]) {
        for (const auto& tile_data : layer_data["tiles"]) {

            if (layer_data["name"] == "props") {

                auto entity = EntityManager::GetInstance().CreateMapEntity("level1");
                entity->is_collidable = layer_data["collider"];
                entity->entity_type = layer_data["name"];
                auto tc = entity->AddComponent<TransformComponent>(tile_data["x"] * SPRITE_SIZE, tile_data["y"] * SPRITE_SIZE);
                auto sc = entity->AddComponent<SpriteComponent>(tc, "assets/level_map/level1/spritesheet.png", SPRITE_SIZE, SPRITE_SIZE);
                std::string id = tile_data["id"];
                sc->SetTextureRect(getSpriteRect(std::stoi(id)));
                tc->scale = { 2, 2 };

            }

            if (layer_data["name"] == "torch") {

                auto entity = EntityManager::GetInstance().CreateMapEntity("level1");
                entity->is_collidable = layer_data["collider"];
                entity->entity_type = layer_data["name"];
                auto tc = entity->AddComponent<TransformComponent>(tile_data["x"] * SPRITE_SIZE, tile_data["y"] * SPRITE_SIZE);
                auto sc = entity->AddComponent<SpriteComponent>(tc, "assets/level_map/level1/torch.png", SPRITE_SIZE * 2, SPRITE_SIZE * 2);
                tc->scale = { 0.5, 0.5 };
                sc->has_animation = true;

            }

        }
    }



   
}

LevelMap::~LevelMap() {



}

void LevelMap::reload_map() {

    std::ifstream level_file;
    level_file.open("assets/level_map/level1/level1.txt");

    if (!level_file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
    }

    std::string line;
    int y = 0;
    while (std::getline(level_file, line)) {
        std::cout << line.size() << std::endl;
        for (size_t x = 0; x < line.size(); ++x) {

            if (line[x] == 'p') {
                EntityManager::GetInstance().GetEntity("player")->GetComponent<TransformComponent>()->position.x = x * SPRITE_SIZE;
                EntityManager::GetInstance().GetEntity("player")->GetComponent<TransformComponent>()->position.y = y * SPRITE_SIZE;
            }
            else if (line[x] == '#') {
                auto entity = EntityManager::GetInstance().CreateMapEntity("level1");
                entity->is_collidable = true;
                auto tc = entity->AddComponent<TransformComponent>(x * SPRITE_SIZE, y * SPRITE_SIZE);
                auto sc = entity->AddComponent<SpriteComponent>(tc, "assets/grass.png", SPRITE_SIZE, SPRITE_SIZE);
            }
            else if (line[x] == 'b') {
                auto entity = EntityManager::GetInstance().CreateMapEntity("level1");
                entity->is_collidable = false;
                auto tc = entity->AddComponent<TransformComponent>(x * SPRITE_SIZE, y * SPRITE_SIZE);
                auto sc = entity->AddComponent<SpriteComponent>(tc, "assets/grass.png", SPRITE_SIZE, SPRITE_SIZE);
            }

        }
        ++y;
    }

    level_file.close();

}

