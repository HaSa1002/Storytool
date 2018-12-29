#include "Connection.hpp"
#include <iostream>

namespace st {
	Connection::Connection(Node & s, Node & e) {
		s_n = s.id;
		e_n = e.id;
		update(s, e);
	}
	bool Connection::is(const std::string & start, const std::string & end) {
		return start == s_n && end == e_n;
	}
	//FIXME: Use also GlobalBounds to find the perfect starting position
	void Connection::update(Node & n_start, Node & n_end) {
		sf::Vector2f s = n_start.getPosition();
		sf::Vector2f e = n_end.getPosition();
		if (s == start && e == end) return; //No update required
		auto s_b = n_start.shape.getGlobalBounds();
		auto e_b = n_end.shape.getGlobalBounds();
		s += { s_b.width/2, s_b.height};
		e += { e_b.width/2, 0};
		
		start = s;
		end = e;
		//Start
		line[0].position = s;
		line[1].position = s;
		line[1].position.y += 10;
		line[2].position = line[1].position;

		//End
		line[5].position = e;
		line[4].position = { e.x, line[2].position.y };
		line[3].position = line[4].position;
		for (size_t i = 0; i < line.getVertexCount(); ++i) {
			line[i].color = sf::Color::Black;
		}

	}

	void Connection::draw(sf::RenderTarget & target, sf::RenderStates states) const {
		target.draw(line, states);
	}
}
