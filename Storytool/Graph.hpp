#pragma once
#include "Config.hpp"
#include "Node.hpp"
#include <SFML/Window/Event.hpp>
#include <unordered_map>


namespace st {
	struct Graph : public sf::Drawable {
		Graph() {};
		Graph(const std::string& id, const std::string& headline, const std::string& description) :id { id }, headline { headline }, description { description } {}
		std::string id;
		std::string headline;
		std::string description;

		std::unordered_map<st::id, Node> nodes;
		std::unordered_map<st::id, st::id> connections;

		Node* hitNode(const sf::Vector2i& pos);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	};
}