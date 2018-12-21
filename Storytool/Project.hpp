#pragma once
#include "Config.hpp"
#include "Character.hpp"
#include "NodeSet.hpp"
#include "Graph.hpp"
#include "Parser.hpp"

namespace st {
	struct Project : public sf::Drawable {
	Project() :name{"Untitled Project"} {};
	Project(const std::string& path);
		std::string name;
		std::unordered_map<id, NodeSet> node_sets;
		std::unordered_map<id, Graph> graphs;
		std::unordered_map<st::name, Character> characters;
		GlobalVars global_vars;
		std::unordered_map<id, std::string> storyline;
		std::string storyline_id_template;

		//Save and load
		xmlData save();
		void load(const std::string& path);


		//Input Handler Functions
		Node* active = nullptr;
		bool hasActiveNode();
		void moveNode(const sf::Vector2f& dest);
		void selectNode(const sf::Vector2f& pos);
		void deselectNode();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	};
}