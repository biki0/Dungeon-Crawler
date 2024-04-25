#include "../include/Game.hpp"

Game::Game() {

	m_window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Simple Dungeon");



	m_camera.zoom(.5f);
	
	SystemManager::GetInstance().AddSystem<CollisionSystem>();
	SystemManager::GetInstance().AddSystem<PhysicsSystem>();
	SystemManager::GetInstance().AddSystem<AnimationSystem>();
	SystemManager::GetInstance().AddSystem<FireBallSystem>();
	SystemManager::GetInstance().AddSystem<SkeletonEnemySystem>();

}

Game::~Game() {

}


void Game::update() {

	while (m_window.pollEvent(m_event)) {
		
		if (m_event.type == sf::Event::Closed) {

			m_window.close();

		}
		if (m_event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			m_window.close();
		}
		if (m_event.type == sf::Event::MouseWheelScrolled) {

			if (m_event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {

				float zoomDelta = 1.0f + m_event.mouseWheelScroll.delta * 0.1f;
				std::cout << m_event.mouseWheelScroll.delta << std::endl;

				m_camera.zoom(zoomDelta);
			}
		}
		if (m_event.type == sf::Event::KeyPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
				m_level_map.reload_map();
			}
		}

	}

	float dt = m_clock.restart().asSeconds();

	const sf::Vector2i mouse_position{ sf::Mouse::getPosition(m_window) };
	const sf::Vector2f mouse_coord{ m_window.mapPixelToCoords(mouse_position) };

	m_player.mouse_position = mouse_coord;
	m_player.update(dt);

	EntityManager::GetInstance().UpdateAll(dt);
	SystemManager::GetInstance().Update(dt);


	m_camera.update();

}

void Game::render() {

	m_window.clear(sf::Color{ 17, 12, 4 });
	m_window.setView(m_window.getDefaultView());

	m_camera.render(m_window);


	EntityManager::GetInstance().RenderLevel(m_window, "level1", m_camera.view);
	EntityManager::GetInstance().RenderEnemies(m_window, "level1", m_camera.view);


	EntityManager::GetInstance().RenderPlayer(m_window, m_camera.view);



	m_window.display();

}

void Game::run() {

	while (m_window.isOpen()) {

		this->update();
		this->render();

	}

}

