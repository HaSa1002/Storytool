#include "Graph.hpp"

namespace st {

	Graph::Graph(sf::Font* font)
		:Graph { "UntitledGraph", "Untitled Graph", "", font } { }


	Graph::Graph(const std::string& id, const std::string& headline, const std::string& description, sf::Font* font)
		: id { id },
		description { description },
		font { font },
		headline { headline, *font } { }


	Node* Graph::hitNode(const sf::Vector2f& pos) {
		for (auto& i : nodes) {
			if (i.second.isHovered(pos))
				return &i.second;
		}
		return nullptr;
	}

	void Graph::update() {
		for (auto& i : connections) {
			auto start = nodes.find(i.s_n);
			auto end = nodes.find(i.e_n);
			if (start == nodes.end() || end == nodes.end()) {

				continue;
			}
			i.update(nodes[i.s_n], nodes[i.e_n]);
		}
	}

	//FIXME: Draw list
	//FIXME: Global Bounds Graph
	//FIMXE: Center Headline
	//FIXME: Draw Bounds
	void Graph::draw(sf::RenderTarget & target, sf::RenderStates states, const std::unordered_map<st::id, Graph>& graphs) const {
		for (auto& n : nodes) {
			target.draw(n.second, states);
		}
		for (auto g : sub_graphs) {
			sf::RenderStates current { states };
			sf::Transformable t;
			t.setPosition(g.second);
			current.transform *= t.getTransform();
			try {
				const Graph& sg = graphs.at(g.first);
				sg.draw(target, current, graphs);
				target.draw(sg.headline, current);
			} catch (std::out_of_range) {
				//Graph doesn't exists
				target.draw(sf::Text { "Graph \"" + g.first + "\" doesn't exists!", *font }, current);
			}
		}
		//Draw connections
		for (auto& i : connections) {
			target.draw(i, states);
		}

		
	}
	void Graph::addNode(const Node * node) {
		Node n = *node;
		n.id = std::to_string(++node_id);
		nodes.insert({ n.id, n });
	}
	void Graph::deleteNode(const std::string & id) {
		nodes.erase(id);
	}
	void Graph::addConnection(const std::string & start, const std::string & end) {
		for (auto& i : connections) {
			if (i.is(start, end)) return; //Don't do double inserts;
			//TODO: Use seperate container to check if connection exists
		}
		connections.push_back({ nodes[start], nodes[end] });
	}
}
