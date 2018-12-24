#pragma once
#include "Config.hpp"
#include "Node.hpp"
#include "Connection.hpp"
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
		std::map<std::pair<std::string, std::string>, Connection> connections;
		size_t node_id = 0;
		Node* hitNode(const sf::Vector2f& pos);

		void update();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void addNode(const Node* node);
		void deleteNode(const std::string& id);
		void addConnection(const std::string& start, const std::string& end);

	};
}