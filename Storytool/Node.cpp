#include "Node.hpp"

void st::Node::draw(sf::RenderTarget & target, sf::RenderStates states) const { 
	target.draw(shape);
	target.draw(rendered_name);

}
