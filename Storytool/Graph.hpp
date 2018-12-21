#pragma once
#include "Config.hpp"
#include "Node.hpp"
#include <SFML/Window/Event.hpp>
#include <unordered_map>


namespace st {
	struct Graph {
		std::string id;
		std::string headline;
		std::string description;

		std::unordered_map<st::id, Node> nodes;
		std::unordered_map<st::id, st::id> connections;
		
		Node* hitNode(const sf::Vector2i& pos);

		
	};
}