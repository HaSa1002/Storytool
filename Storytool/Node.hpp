#pragma once
#include "Config.hpp"
#include "Action.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include <unordered_set>

namespace st {
	struct Node {
		
		sf::RectangleShape shape;
		id belongsToChar;
		std::string id;
		sf::Text rendered_name;
		std::unordered_set<st::id> storylines;
		std::vector<st::id> actions;


	};
}