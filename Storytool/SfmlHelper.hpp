#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <cmath>

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

	template<class T>
	static T length(const Vector2<T>& v);

	template<class T>
	static T length(const Vector2<T>& v) {
		return static_cast<T>(std::hypot<T, T>(v.x, v.y));
	}
}