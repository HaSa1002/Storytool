#pragma once
#include "Config.hpp"
#include "Node.hpp"
#include <unordered_map>


namespace st {
	struct Graph {
		std::string name;
		std::string headline;
		std::string description;

		
		std::unordered_map<id, Node> nodes;
		std::unordered_map<id, id> connections;

		
	};
}