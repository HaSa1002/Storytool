#pragma once
#include "Config.hpp"

namespace st {

	struct Action {
		std::string name;
		std::string description;
		char action[2]; // Can be =, +, -, /, *, ! <-- defines the action
		id variable;
		long amount;

	};

}