#pragma once
#include "Project.hpp"
#include "Serialize.hpp"
#include "Deserialize.hpp"

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
		void drawGraphOverview();
		void draw();
		void mainMenuBar();

		void drawGlobalsWindow();


	private:
	std::unordered_map<std::string, bool> window_states{
		{"character", false },
		{"property", true },
		{"storyline", false },
		{"globalvars", false },
		{"graphoverview", true },
		{"nodecollection", true },
		{"right-click-menu", false }
	};

	Project project;

	sf::Vector2i last_mousePos;
	float zoomfactor = 1.f;
	bool node_moving = false;
	sf::Vector2f move_offset;

	//Node adding
	Node* to_add;

	//Connection line stuff
	sf::VertexArray line{sf::PrimitiveType::LineStrip, 2 };
	bool connecting_nodes = false;
	std::string start_node;

	sf::RenderWindow win;
	sf::Clock clock;
	sf::Font font;
	

	//Doubleclick detection
	sf::Time doubleClickTime;
	sf::Time last_click = sf::Time::Zero;
	};
}
