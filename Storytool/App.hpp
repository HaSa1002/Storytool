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
		{"actions", false }
	};

	Project project;

	

	sf::RenderWindow win;
	sf::Clock clock;
	};
}
