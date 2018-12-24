#pragma once
#include "Node.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

namespace st {
	struct Connection : sf::Drawable {
		Connection(Node& s, Node& e);
		sf::Vector2f start;
		sf::Vector2f end;
		sf::VertexArray line{sf::PrimitiveType::LineStrip, 6 };

		void update(Node& n_start, Node& n_end);
		void draw(sf::RenderTarget& target, sf::RenderStates) const;
	};
}