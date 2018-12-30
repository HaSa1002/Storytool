#pragma once
#include "Node.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

namespace st {
	struct Connection : sf::Drawable {
		Connection(Node& s, Node& e);
		Connection(const std::string& s, const std::string& e);
		std::string s_n;
		std::string e_n;
		sf::Vector2f start;
		sf::Vector2f end;
		sf::VertexArray line{sf::PrimitiveType::LineStrip, 6 };

		bool is(const std::string& start, const std::string& end);

		void update(Node& n_start, Node& n_end);
		void draw(sf::RenderTarget& target, sf::RenderStates) const;
	};
}