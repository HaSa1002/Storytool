#include "Graph.hpp"

namespace st {

	Node* Graph::hitNode(const sf::Vector2f& pos) {
		for (auto& i : nodes) {
			if (i.second.isHovered(pos))
				return &i.second;
		}
		return nullptr;
	}

	void Graph::update() { 
		for (auto i : connections) {
			auto start = nodes.find(i.first.first);
			auto end = nodes.find(i.first.second);
			if (start == nodes.end() || end == nodes.end()) {
				connections.erase(i.first);
				continue;
			}
			i.second.update(start->second, end->second);
		}
	}

	//FIXME: Draw list
	void Graph::draw(sf::RenderTarget & target, sf::RenderStates states) const {
		for (auto& n : nodes) {
			target.draw(n.second);
		}
		//Draw connections
		for (auto& i : connections) {
			target.draw(i.second);
		}

		//Draw headline
	}
	void Graph::addNode(const Node * node) {
		Node n = *node;
		n.id = std::to_string(++node_id);
		nodes.insert({ n.id, n });
	}
	void Graph::deleteNode(const std::string & id) { 
		nodes.erase(id);
	}
}
