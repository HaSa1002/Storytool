#pragma once
#include "Project.hpp"
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
		void mainMenuBar();


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
	//Test
	std::string buff;
	GlobalVars global_vars;

	sf::RenderWindow win;
	sf::Clock clock;
	};
}
