#include "Graph.hpp"

namespace st {

	Node* Graph::hitNode(const sf::Vector2i& pos) {
			for (auto& i : nodes) {
				if (i.second.isHovered(pos))
					return &i.second;
			}
		return nullptr;
	}
}
