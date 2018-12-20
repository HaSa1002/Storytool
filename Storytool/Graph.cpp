#include "Graph.hpp"

void st::Graph::handleMouseClick(sf::Event::MouseButtonEvent & event) {
	if (event.button == sf::Mouse::Button::Right) {
		selected == nullptr;
	} //... Add all possible cases here

	if (selected == nullptr) {
		for (auto i : nodes) {
			if (i.second.isHovered({ event.x, event.y })) {
				selected = &i.second;
			}
		}
	} else {

	}
}
