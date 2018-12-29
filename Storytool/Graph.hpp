#pragma once
#include "Config.hpp"
#include "Node.hpp"
#include "Connection.hpp"
#include <SFML/Graphics/Font.hpp>
#include <unordered_map>
#include <iostream>


namespace st {
	struct Graph {
		Graph() = default;
		Graph(const std::string& id, const std::string& headline, const std::string& description, sf::Font* font);

		Graph(sf::Font* font);
		std::string id;
		sf::Text headline;
		std::string description;

		sf::Font* font;

		std::unordered_map<st::id, Node> nodes;
		std::vector<Connection> connections;
		std::vector<std::pair<name, sf::Vector2f>> sub_graphs;
		size_t node_id = 0;
		Node* hitNode(const sf::Vector2f& pos);

		void update();
		void draw(sf::RenderTarget& target, sf::RenderStates states, const std::unordered_map<st::id, Graph>& graphs) const;
		void addNode(const Node* node);
		void deleteNode(const std::string& id);
		void addConnection(const std::string& start, const std::string& end);


	};
}