#include "Node.hpp"

void st::Node::draw(sf::RenderTarget & target, sf::RenderStates states) const { 
	target.draw(shape);
	target.draw(rendered_name);

}

void st::Node::correctTransforms() {
	
	auto p = shape.getPosition();
	p += sf::Vector2f(offset, offset);
	rendered_name.setPosition(p);
	auto s = rendered_name.getLocalBounds();
	sf::extrude<float>(s, 4*offset);
	shape.setSize({s.width-offset, s.height});
}
