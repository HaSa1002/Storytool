#pragma once
#include <AF/xml.hpp>
#include <string>
#include <unordered_map>


namespace st {
	using name = std::string;
	using id = std::string;
	using xmlData = af::XML::Structure;
	using GlobalVars = std::unordered_map<name, double>;
}
