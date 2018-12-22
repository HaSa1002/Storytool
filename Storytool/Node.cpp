#include "Node.hpp"

void st::Node::draw(sf::RenderTarget & target, sf::RenderStates states) const { 
	target.draw(shape);
	target.draw(rendered_name);

}

void st::Node::correctTransforms() {
	
	auto p = shape.getPosition();
	auto bounds = rendered_name.getGlobalBounds();
	sf::extrude<float>(bounds, offset);
	shape.setPosition(bounds.left, bounds.top);
	shape.setSize({ bounds.width + offset, bounds.height + offset});
}

void st::Node::setPosition(const sf::Vector2f & position) { 
	rendered_name.move(position - getPosition());
	correctTransforms();
}

void st::Node::setDisplayString(const std::string & string) { 
	rendered_name.setString(string);
	correctTransforms();
}

bool st::Node::isHovered(const sf::Vector2f & mouse_pos) {
	if (shape.getGlobalBounds().contains(mouse_pos)) {
		shape.setOutlineColor(sf::Color::Black);
		shape.setOutlineThickness(1);
		return true;
	}
	shape.setOutlineThickness(0);
	return false;
}

sf::Vector2f st::Node::getPosition() {
	auto bounds = rendered_name.getGlobalBounds();
	sf::extrude<float>(bounds, offset);
	return sf::Vector2f(bounds.left, bounds.top);
}
