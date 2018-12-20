#pragma once
#include "Config.hpp"
#include "Node.hpp"
#include <SFML/Window/Event.hpp>
#include <unordered_map>


namespace st {
	struct Graph {
		std::string name;
		std::string headline;
		std::string description;

		Node* selected = nullptr;
		bool isActive = false;
		std::unordered_map<id, Node> nodes;
		std::unordered_map<id, id> connections;
		//maybe return bool?
		void handleMouseClick(sf::Event::MouseButtonEvent& event);

		
	};
}