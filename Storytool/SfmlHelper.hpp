#pragma once
#include <SFML/Graphics/Rect.hpp>

namespace sf {
	template<class T>
	static void extrude(sf::Rect<T>& r, T offset);
	template<class T>
	static void extrude(sf::Rect<T>& r, T offset) {
		r.top -= offset;
		r.left -= offset;
		r.height += offset;
		r.width += offset;
	}
}