#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "../util/Category.hpp"
#include "SFML\System\Time.hpp"
#include <functional>
//#include <cassert>

class SceneNode;

struct Command{
	Command();
	std::function<void(SceneNode&, sf::Time)> action;
	unsigned int category;
};
#endif