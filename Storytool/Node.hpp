#pragma once
#include "Config.hpp"
#include "SfmlHelper.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include <unordered_set>

namespace st {
	const float offset = 10.f;
	struct Node : sf::Drawable {
	Node() {};
		Node(const std::string& id, const st::id& character, const std::string& rendered_name, sf::Font& font): id{id}, character{character}, rendered_name{rendered_name, font} {};
		Node(const std::string& id, const st::id& character, const std::string& rendered_name,
		sf::Font& font, const sf::Color& bg_color, const sf::Color& t_color, 
		const sts& is_activated, const sts& after_execute) : id { id }, character { character },
		rendered_name { rendered_name, font }, 
		is_activated{is_activated}, after_execute{after_execute} {
			this->rendered_name.setFillColor(t_color);
			shape.setFillColor(bg_color);
		};
		Node(const Node& n) :id{n.id}, character{n.character}, rendered_name{n.rendered_name},
		shape{n.shape}, storylines{n.storylines}, is_activated{n.is_activated}, after_execute{n.after_execute} {}

		
		std::string id;
		st::id character;
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