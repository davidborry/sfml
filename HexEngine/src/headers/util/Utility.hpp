#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <sstream>

namespace sf{
	class Sprite;
	class Text;
}

// Since std::to_string doesn't work on MinGW we have to implement
// our own to support all platforms.
template<typename T>
std::string toString(const T& value){
	std::stringstream stream;
	stream << value;
	return stream.str();
}

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);

float toDegree(float radian);
float toRadian(float degree);

#endif