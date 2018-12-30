#pragma once

#include "Project.hpp"
#include "AF/xml.hpp"
#include <SFML/Graphics/Color.hpp>
#include <cassert>

namespace Deserialize {
	using constxml = const af::XML::Structure&;
	using xml = af::XML::Structure;

	auto Color(constxml data)->const sf::Color;

	auto Vector2f(const std::string& s)->sf::Vector2f;

	auto Text(constxml d)->sf::Text;

	auto String(constxml data, const std::string& expected_key) ->const std::string;

	auto UnorderedSet(constxml d, const std::string& item_name) ->const std::unordered_set<std::string>;

	auto Character(constxml data)->const st::Character;

	auto Project(constxml d, sf::Font* font)->const st::Project;

	auto Characters(constxml d)->const std::vector<st::Character>;

	auto Storyline(constxml d)->const std::pair<std::string, std::string>;

	auto Storylines(constxml d)->const std::unordered_map<std::string, std::string>;

	auto Node(constxml d)-> const st::Node;

	auto Nodes(constxml d)->const std::unordered_map<std::string, st::Node>;

	auto Connection(constxml d) ->const st::Connection;

	auto Connections(constxml d)->const std::vector<st::Connection>;

	auto Subgraph(constxml d)->const std::pair<std::string, sf::Vector2f>;

	auto Subgraphs(constxml d)->const std::vector<std::pair<std::string, sf::Vector2f>>;

	auto Graph(constxml d)->const st::Graph;

	auto Graphs(constxml d)->const std::unordered_map<std::string, st::Graph>;

	auto GlobalVar(constxml d)->const std::pair<std::string, double>;

	auto GlobalVars(constxml d)->const st::GlobalVars;

}