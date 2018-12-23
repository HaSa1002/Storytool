#pragma once
#include "Project.hpp"

#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>

namespace st {
	class App {
	public:
		App();
		~App();

	private:
		void main();
		void processEvents();
		void update();
		void drawStorylineWindow();
		void drawCharacterWindow();
		void drawNodeCollection();
		void drawPropertyEditor();
		void drawRightClickMenu();
		void draw();
		void mainMenuBar();

		void drawGlobalsWindow();


	private:
	std::unordered_map<std::string, bool> window_states{
		{"character", false },
		{"property", true },
		{"storyline", true },
		{"globalvars", false },
		{"graphoverview", false },
		{"nodecollection", true },
		{"actions", false },
		{"right-click-menu", false }
	};

	Project project;

	sf::Vector2i last_mousePos;
	float zoomfactor = 1.f;
	bool node_moving = false;
	sf::Vector2f move_offset;

	//Node adding
	Node* to_add;

	sf::RenderWindow win;
	sf::Clock clock;
	sf::Font font;
	};
}
