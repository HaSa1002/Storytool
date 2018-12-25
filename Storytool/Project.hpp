#pragma once
#include "Config.hpp"
#include "Character.hpp"
#include "Graph.hpp"
#include "Parser.hpp"

namespace st {
	struct Project : public sf::Drawable {
	Project() :name{"Untitled Project"} {
		graphs["main"] = Graph{"main", "", "The main Graph in the project." };
		current_graph = &graphs["main"];
	};
	Project(const std::string& path);
		std::string name;
		std::unordered_map<id, Node> def_nodes;
		std::unordered_map<id, Graph> graphs;
		std::vector<Character> characters;
		GlobalVars global_vars;

		//Storyline
		//FIXME: Add counter var, add addStoryline(id, text) method;
		std::unordered_map<id, std::string> storyline;
		std::string storyline_id_template = "C-I";
		size_t storyline_counter = 0;
		const std::string proposeStorylineID();
		void addStoryline(const std::string& text);
		void addStoryline(const std::string& text, const std::string& id);
		

		id main_graph;

		//Save and load
		xmlData save();
		void load(const std::string& path);


		//Input Handler Functions
		Node* active = nullptr;
		Graph* current_graph= nullptr;
		bool hasActiveNode();
		void moveNode(const sf::Vector2f& dest);
		void selectNode(const sf::Vector2f& pos);
		void addNode(const Node* node);
		void deleteNode(const std::string& id);
		void deselectNode();
		void addConnection(const std::string& start, const std::string& end);

		//Drawing
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void update();

	};
}