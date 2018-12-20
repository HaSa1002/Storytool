#include "Node.hpp"

void st::Node::draw(sf::RenderTarget & target, sf::RenderStates states) const { 
	target.draw(shape);
	target.draw(rendered_name);

}

void st::Node::correctTransforms() {
	
	auto p = shape.getPosition();
	//p += sf::Vector2f(offset, offset);
	//rendered_name.setPosition(p);
	rendered_name.setCharacterSize(310);
	auto bounds = rendered_name.getGlobalBounds();
	sf::extrude<float>(bounds, offset);
	shape.setPosition(bounds.left, bounds.top);
	shape.setSize({ bounds.width + offset, bounds.height + offset});
}

void st::Node::setPosition(const sf::Vector2f & position) { 
	rendered_name.setPosition(position);
	correctTransforms();
}

void st::Node::setDisplayString(const std::string & string) { 
	rendered_name.setString(string);
	correctTransforms();
}

bool st::Node::isHovered(const sf::Vector2i & mouse_pos) {
	return shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos));
}
