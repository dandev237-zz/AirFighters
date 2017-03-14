#pragma once

#include <functional>
#include <SFML\System\Time.hpp>

#include "Category.h"

class SceneNode;

struct Command
{
	Command();

	//Callback
	std::function<void(SceneNode&, sf::Time)> action;
	unsigned int category;

	template <typename GameObject, typename Function>
	std::function<void(SceneNode&, sf::Time)> Command::derivedAction(Function function)
	{
		return [=](SceneNode& node, sf::Time deltaTime)
		{
			//Cast safety check
			assert(dynamic_cast<GameObject*>(&node) != nullptr);

			//Downcast node and invoke function on it
			function(static_cast<GameObject&>(node), deltaTime);
		};
	}

};

