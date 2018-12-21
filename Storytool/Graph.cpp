#include "Graph.hpp"

namespace st {

	Node* Graph::hitNode(const sf::Vector2f& pos) {
			for (auto& i : nodes) {
				if (i.second.isHovered(pos))
					return &i.second;
			}
		return nullptr;
	}

	//FIXME: Draw list
	void Graph::draw(sf::RenderTarget & target, sf::RenderStates states) const { 
		for (auto& n : nodes) {
			target.draw(n.second);
		}
		//Draw connections

		//Draw headline
	}
}
