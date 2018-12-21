#pragma once
#include "Project.hpp"
#include "Node.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include "imgui.h"
#include "imgui-SFML.h"

namespace st {
	class App {
	public:
		App();
		~App();

	private:
		void main();
		void processEvents();
		void update();
		void drawRightClickMenu();
		void draw();
		void mainMenuBar();

		void drawGlobalsWindow();


	private:
	std::unordered_map<std::string, bool> window_states{
		{"character", false },
		{"property", false },
		{"storyline", false },
		{"globalvars", false },
		{"graphoverview", false },
		{"nodecollection", false },
		{"actions", false },
		{"right-click-menu", false }
	};

	Project project;

	sf::Vector2i last_mousePos;
	float zoomfactor = 1.f;

	sf::RenderWindow win;
	sf::Clock clock;
	};
}
