#pragma once
#include "Config.hpp"
#include "Character.hpp"
#include "ActionSet.hpp"
#include "NodeSet.hpp"
#include "Graph.hpp"
#include "Parser.hpp"

namespace st {
	struct Project {
		std::string name;
		ActionSet actionSet;
		std::unordered_map<id, NodeSet> node_sets;
		std::unordered_map<id, Graph> graphs;
		std::unordered_map<st::name, Character> characters;
		GlobalVars global_vars;
		std::unordered_map<id, std::string> storyline;
		std::string storyline_id_template;


		xmlData save();
		


	};
}