#pragma once
#include "Config.hpp"
#include "SfmlHelper.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include <unordered_set>

namespace st {
	struct Node : sf::Drawable {
		const float offset = 10.f;
	Node() {};
		Node(const std::string& id, const std::string& t_id, const std::string& rendered_name, sf::Font& font): id{id}, type_id{t_id}, rendered_name{rendered_name, font} {};
		std::string id;
		std::string type_id;
		sf::Text rendered_name;
		sf::RectangleShape shape;
		std::unordered_set<st::id> storylines;
		sts is_activated;
		sts after_execute;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void correctTransforms(); // Apply correct size to sf::Shape
		void setPosition(const sf::Vector2f& position); //sets the position and calls correctTransforms
		void setDisplayString(const std::string& string); //sets the displayed string and calls correctTransforms
		bool isHovered(const sf::Vector2f& mouse_pos);
		sf::Vector2f getPosition();

	};
}