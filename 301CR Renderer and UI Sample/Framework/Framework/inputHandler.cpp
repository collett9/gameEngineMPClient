#include "inputHandler.h"



inputHandler::buttons inputHandler::whichKey()
{
	rendererEvent->gameWindow->pollEvent(eventToHandle);

	if (eventToHandle.type == sf::Event::Closed) {
		return closed;

	}

	/*
	If the event isn't an Event::Closed, we check to see if it's an Event::KeyPressed. If so,
	we run through a check to see if an arrow key is being pressed. Dependent on the key(s) being
	pressed, our textured square moves in different directions. This approach has several issues
	as discussed in the lecture, so you'll want to abstract and refine this. Can you think of any
	problems which might occur when two keys are pressed simultaneously?

	Next, if the Escape key is pressed, we consider that to be a close instruction from the user
	and the window exits.
	*/

	if (eventToHandle.type == sf::Event::KeyPressed)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			return leftArrow;
			
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			return rightArrow;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			return upArrow;
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			return downArrow;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			return space;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			return W;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			return escape;
		}
	}
	if (eventToHandle.type == sf::Event::Resized)
	{
		sf::FloatRect visibleArea(0, 0, eventToHandle.size.width, eventToHandle.size.height);
		rendererEvent->gameWindow->setView(sf::View(visibleArea));
		return resized;
	}

}

void inputHandler::setUpEvent(sf::Event whichEvent)
{
	eventToHandle = whichEvent;
}

void inputHandler::setUpRenderer(renderer * rendererToUse)
{
	 rendererEvent = rendererToUse;
}

inputHandler::inputHandler()
{
}


inputHandler::~inputHandler()
{
}
