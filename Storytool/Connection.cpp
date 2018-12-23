#include "Connection.hpp"

namespace st {
//FIXME: Use also GlobalBounds to find the perfect starting position
	void Connection::update(Node & n_start, Node & n_end) {
		sf::Vector2f s = n_start.getPosition();
		sf::Vector2f e = n_end.getPosition();
		if (s == start && e == end) return; //No update required

		//Start
		line[0].position = s;
		line[1].position = s;
		line[1].position.y += 10;
		line[2].position = line[1].position;

		//End
		line[5].position = e;
		line[4].position = { e.x, line[2].position.y };
		line[3].position = line[4].position;

		start = s;
		end = e;
	}

	void Connection::draw(sf::RenderTarget & target, sf::RenderStates) const {
		target.draw(line);
	}
}
