#include "Deserialize.hpp"

namespace Deserialize {
	auto Color(constxml data) -> const sf::Color {
		assert(data.key == "color");
		return sf::Color { std::stoul(data.content) };
	}

	auto Vector2f(const std::string & s) -> sf::Vector2f {
		assert(s[0] == '2'); //Not 2 dimensional vector
		assert(s[1] == 'f'); //Not Float Vector
		size_t start = s.find('(') + 1;
		size_t middle = s.find('|') + 1;
		return sf::Vector2f { std::stof(s.substr(start, middle - start)), std::stof(s.substr(middle, s.size() - middle - 1)) };
	}

	auto Text(constxml d) -> sf::Text {
		assert(d.key == "text"); //Not Text
		assert(d.childs.size() == 2); //Not correct number of childs;
		sf::Text t;
		t.setString(d.content);
		char size = 0;
		char color = 1;
		if (d.childs[size].key != "size") {
			size = 1;
			color = 0;
		}
		t.setCharacterSize(std::stoul(String(d.childs[size], "size")));
		t.setFillColor(Color(d.childs[color]));
		return t;
	}


	auto Project(constxml d, sf::Font* font) -> const st::Project {
		assert(d.key == "storytool"); //Wrong File
		assert(std::stoi(d.attributes.at("file")) >= st::MIN_FILE_VER);
		xml p = d.childs[0];
		assert(p.key == "project");
		st::Project proj { font };
		proj.name = p.attributes["name"];
		proj.main_graph = p.attributes["main-graph"];

		for (auto i : p.childs) {
			if (i.key == "characters") {
				proj.characters = Characters(i);
			} else if (i.key == "storyline") {
				proj.storyline = Storylines(i.childs[0]);
				proj.storyline_counter = proj.storyline.size();
				proj.storyline_id_template = i.attributes["template"];
			} else if (i.key == "globals") {
				proj.global_vars = GlobalVars(i);
			} else if (i.key == "nodes") {
				proj.node_set = Nodes(i);
			} else if (i.key == "graphs") {
				proj.graphs = Graphs(i);
			} else {
				assert(false); //Unknown key
			}
		}
		//Font setting...
		for (auto i : proj.graphs) {
			i.second.font = font;
			i.second.headline.setFont(*font);
			for (auto j : i.second.nodes) {
				j.second.rendered_name.setFont(*font);
			}
		}

		return proj;
	}


	auto String(constxml data, const std::string & expected_key) -> const std::string {
		assert(data.key == expected_key);
		return data.content;
	}


	auto UnorderedSet(constxml d, const std::string& item_name) -> const std::unordered_set<std::string> {
		assert(d.key == item_name + 's'); //Not a set
		std::unordered_set<std::string> res;
		for (auto i : d.childs)
			res.insert(String(i, item_name));
		return res;
	}


	auto Character(constxml data) -> const st::Character {
		assert(data.key == "character");
		assert(data.attributes.find("name") != data.attributes.end());
		assert(data.childs.size() == 2);
		char description = 0;
		char color = 1;
		if (data.childs[0].key != "description") {
			description = 1;
			color = 0;
		}

		return st::Character { data.attributes.at("name"),
		String(data.childs[description], "description"),
		Color(data.childs[color]) };
	}

	auto Characters(constxml d) -> const std::vector<st::Character> {
		assert(d.key == "characters");
		std::vector<st::Character> res;
		for (auto i : d.childs)
			res.push_back(Character(i));
		return res;
	}


	auto Storyline(constxml d) -> const std::pair<std::string, std::string> {
		assert(d.key == "line");
		return std::pair<std::string, std::string>(d.attributes.at("id"), d.content);
	}


	auto Storylines(constxml d) -> const std::unordered_map<std::string, std::string> {
		std::unordered_map<std::string, std::string> res;
		for (auto i : d.childs) {
			auto l = Storyline(i);
			res[l.first] = l.second;
		}
		return res;
	}


	auto Node(constxml d) -> const st::Node {
		assert(d.key == "node");
		st::Node n;
		n.id = d.attributes.at("id");
		n.character = d.attributes.at("character");
		for (auto i : d.childs) {
			if (i.key == "nodestyle") {
				for (auto j : i.childs) {
					if (j.key == "text") {
						n.rendered_name = Text(j);
					} else if (j.key == "color") {
						n.shape.setFillColor(Color(j));
					} else {
						assert(false); //Wrong entry
					}
				}
				n.setPosition(Vector2f(i.attributes["position"]));
			} else if (i.key == "storylines") {
				n.storylines = UnorderedSet(i, "storyline");
			} else if (i.key == "is_activated") {
				n.is_activated = String(i, "is_activated");
			} else if (i.key == "after_execute") {
				n.after_execute = String(i, "after_execute");
			} else {
				assert(false); //Wrong entry
			}
		}
		return n;
	}


	auto Nodes(constxml d) -> const std::unordered_map<std::string, st::Node> {
		std::unordered_map<std::string, st::Node> res;
		for (auto i : d.childs) {
			auto n = Node(i);
			res[n.id] = n;
		}
		return res;
	}


	auto Connection(constxml d) -> const st::Connection {
		assert(d.key == "connection");
		return st::Connection(d.attributes.at("start"), d.attributes.at("end"));
	}


	auto Connections(constxml d) -> const std::vector<st::Connection> {
		assert (d.key == "connections");
		std::vector<st::Connection> res;
		for (auto i : d.childs)
			res.push_back(Connection(i));
		return res;
	}


	auto Subgraph(constxml d) -> const std::pair<std::string, sf::Vector2f> {
		assert(d.key == "subgraph");
		return std::pair<std::string, sf::Vector2f>(d.attributes.at("id"), Vector2f(d.content));
	}


	auto Subgraphs(constxml d) -> const std::vector<std::pair<std::string, sf::Vector2f>> {
		assert(d.key == "subgraphs");
		std::vector<std::pair<std::string, sf::Vector2f>> res;
		for (auto i : d.childs)
			res.push_back(Subgraph(i));
		return res;
	}


	auto Graph(constxml d) -> const st::Graph {
		assert(d.key == "graph");
		st::Graph g;
		g.id = d.attributes.at("id");
		for (auto i : d.childs) {
			if (i.key == "text") {
				g.headline = Text(i);
			} else if (i.key == "description") {
				g.description = String(i, "description");
			} else if (i.key == "connections") {
				g.connections = Connections(i);
			} else if (i.key == "subgraphs") {
				g.sub_graphs = Subgraphs(i);
			} else if (i.key == "nodes"){
				g.nodes = Nodes(i);
			} else {
				assert(false); //Wrong entry
			}
		}
		g.node_id = g.nodes.size();
		return g;
	}


	auto Graphs(constxml d) -> const std::unordered_map<std::string, st::Graph> {
		assert(d.key == "graphs");
		std::unordered_map<std::string, st::Graph> res;
		for (auto i : d.childs) {
			auto g = Graph(i);
			res[g.id] = g;
		}
		return res;
	}


	auto GlobalVar(constxml d) -> const std::pair<std::string, double> {
		assert(d.key == "global");
		return std::pair<std::string, double>(d.attributes.at("id"), std::stod(d.content));
	}


	auto GlobalVars(constxml d) -> const st::GlobalVars {
		assert(d.key == "globals");
		st::GlobalVars res;
		for (auto i : d.childs)
			res.insert(GlobalVar(i));
		return res;
	}
}