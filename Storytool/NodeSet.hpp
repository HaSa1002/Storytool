#pragma once
#include "Node.hpp"
#include <unordered_map>


namespace st {
	struct NodeSet {
		std::string id;
		std::unordered_set<st::id, Node> nodes;

		NodeSet(std::string id) :id{id},nodes{} {};
		NodeSet(std::string id, xmlData data);
	};


}