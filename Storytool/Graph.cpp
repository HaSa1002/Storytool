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
	void Graph::draw(sf::RenderTarget & target, sf::RenderStates states) const {
		for (auto& n : nodes) {
			target.draw(n.second);
		}
		//Draw connections
		for (auto& i : connections) {
			target.draw(i);
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
	void Graph::addConnection(const std::string & start, const std::string & end) {
		for (auto& i : connections) {
			if (i.is(start, end)) return; //Don't do double inserts;
			//TODO: Use seperate container to check if connection exists
		}
		connections.push_back({nodes[start], nodes[end] });
		}
	}
