#pragma once

#include "Project.hpp"
#include "Character.hpp"
#include "AF/xml.hpp"
#include <SFML/Graphics/Color.hpp>



namespace Serialize {
	using xml = af::XML::Structure;

	xml Color(const sf::Color& c);

	template<typename T, char tn>
	auto Vector2(const sf::Vector2<T>& v) -> const std::string;

	xml Text(const sf::Text& t);

	xml String(const std::string& key, const std::string& value);

	xml UnorderedSet(const std::unordered_set<std::string>& set, const std::string& item_name);

	xml Character(const st::Character& c);

	xml Project(const st::Project& p);

	xml Characters(const std::vector<st::Character>& c);

	xml Storyline(const std::string& id, const std::string& line);
	xml Storyline(const std::pair<std::string, std::string>& line);

	xml Storylines(const std::unordered_map<std::string, std::string>& storylines);

	xml StorylineBlock(const std::unordered_map<std::string, std::string>& storylines, const std::string& id_template);

	xml Node(const st::Node& n);

	xml NodeStyle(const st::Node& n);

	xml Nodes(const std::unordered_map<std::string, st::Node>& nodes);

	xml Connection(const st::Connection& c);

	xml Connections(const std::vector<st::Connection>& c);

	xml Subgraph(const std::pair<std::string, sf::Vector2f>& s);

	xml Subgraphs(const std::vector<std::pair<std::string, sf::Vector2f>>& s);

	xml Graph(const st::Graph& g);

	xml Graphs(const std::unordered_map<std::string, st::Graph>& g);

	xml GlobalVar(const std::pair<std::string, double>& g);
	
	xml GlobalVars(const st::GlobalVars& g);








	template<typename T, char tn>
	auto Vector2(const sf::Vector2<T>& v) -> const std::string {
		std::string r{ '2' };
		r += tn;
		r += '(';
		r += std::to_string(v.x);
		r += '|';
		r += std::to_string(v.y);
		r += ')';
		return r;
	}
}