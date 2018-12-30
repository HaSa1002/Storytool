#include "Serialize.hpp"

namespace Serialize {
	xml Color(const sf::Color & c) {
		return xml { "color", {}, std::to_string(c.toInteger()) };
	}

	xml Character(const st::Character& c) {
		return xml { "character", {{"name", c.name}}, "",
		{Color(c.color), String("description", c.description)} };
	}

	xml Text(const sf::Text & t) {
		return xml{"text", {}, t.getString(), {
		String("size", std::to_string(t.getCharacterSize())),
		Color(t.getFillColor())
		}};
	}

	xml String(const std::string & key, const std::string & value) {
		return xml { key, {}, value };
	}

	xml UnorderedSet(const std::unordered_set<std::string>& set, const std::string & item_name) {
		xml result { item_name + "s" };
		for (auto i : set)
			result.childs.push_back(String(item_name, i));
		return result;
	}

	xml Project(const st::Project & p) {
		return xml {
			"storytool", {
			{"file", std::to_string(st::FILE_VERSION) },
			{"created-with", std::to_string(st::VERSION_NUM) },
			}, "",{
			{ "project", {
				{ "name", p.name }, {"main-graph", p.main_graph} }, "", {
					Characters(p.characters),
					StorylineBlock(p.storyline, p.storyline_id_template),
					GlobalVars(p.global_vars),
					Nodes(p.node_set),
					Graphs(p.graphs)
				}
			}
			}
		};
	}

	xml Characters(const std::vector<st::Character>& c) {
		xml result { "characters" };
		for (auto i : c)
			result.childs.push_back(Character(i));
		return result;
	}

	xml Storyline(const std::string & id, const std::string & line) {
		return xml { "line", {{"id", id}}, line };
	}

	xml Storyline(const std::pair<std::string, std::string>& line) {
		return Storyline(line.first, line.second);
	}

	xml Storylines(const std::unordered_map<std::string, std::string>& storylines) {
		xml result { "storylines" };
		for (auto l : storylines)
			result.childs.push_back(Storyline(l));
		return result;
	}

	xml StorylineBlock(const std::unordered_map<std::string, std::string>& storylines, const std::string & id_template) {
		return xml { "storyline", {{"template", id_template}}, "", {Storylines(storylines)} };
	}

	xml Node(const st::Node & n) {
		return xml { "node", {
				{"id", n.id},
				{"character", n.character}
			}, "", {
				NodeStyle(n),
				UnorderedSet(n.storylines, "storyline"),
				String("is_activated", n.is_activated),
				String("after_execute", n.after_execute)
			}
		};

	}

	xml NodeStyle(const st::Node & n) {
		return xml{"nodestyle", {{"position", Vector2<float, 'f'>(n.getPosition())}}, "",
		{ Text(n.rendered_name),
			Color(n.shape.getFillColor())
		}};
	}

	xml Nodes(const std::unordered_map<std::string, st::Node>& nodes) {
		xml result { "nodes" };
		for (auto n : nodes)
			result.childs.push_back(Node(n.second));
		return result;
	}

	xml Connection(const st::Connection & c) {
		return xml{"connection", {{"start", c.s_n}, {"end", c.e_n}}};
	}

	xml Connections(const std::vector<st::Connection>& c) {
		xml result{"connections"};
		for (auto i : c)
			result.childs.push_back(Connection(i));
		return result;
	}

	xml Subgraph(const std::pair<std::string, sf::Vector2f>& s) {
		return xml{"subgraph", {{"id", s.first}}, Vector2<float, 'f'>(s.second)};
	}

	xml Subgraphs(const std::vector<std::pair<std::string, sf::Vector2f>>& s) {
		xml result{"subgraphs"};
		for(auto i : s)
			result.childs.push_back(Subgraph(i));
		return result;
	}

	xml Graph(const st::Graph & g) {
		return xml{"graph", {{"id", g.id}}, "", {
			Text(g.headline),
			String("description", g.description),
			Nodes(g.nodes),
			Connections(g.connections),
			Subgraphs(g.sub_graphs)
		}};
	}

	xml Graphs(const std::unordered_map<std::string, st::Graph>& g) {
		xml result{"graphs"};
		for (auto i : g)
			result.childs.push_back(Graph(i.second));
		return result;
	}

	xml GlobalVar(const std::pair<std::string, double>& g) {
		return xml{"global", {{"id", g.first}}, std::to_string(g.second)};
	}

	xml GlobalVars(const st::GlobalVars & g) {
		xml result{"globals"};
		for(auto i : g)
			result.childs.push_back(GlobalVar(i));
		return result;
	}

	

}

