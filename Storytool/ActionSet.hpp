#pragma once
#include "Config.hpp"
#include "Action.hpp"
#include <map>

namespace st {
	struct ActionSet {
		ActionSet(std::string id) : id{id} {};
		ActionSet(std::string id, xmlData data);
		std::string id;
		std::map<name, Action> actions;

		xmlData save();

	};
}