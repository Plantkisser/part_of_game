#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include "core.h"
#include "view.h"
#include "player.h"



int main()
{
	sf:: RenderWindow window(sf:: VideoMode(500, 500), "First");

	sf:: View view;
	view.reset(sf:: FloatRect(0, 0, 600, 600));

	sf:: Clock clock;

	sf:: RectangleShape rectangle(sf:: Vector2f(200, 200)); //????
	rectangle.setFillColor(sf::Color(255, 255, 255));

	rectangle.setPosition(-10, -20);


	std:: vector <GameObject*> o;
	for (int i = 0; i < 5; i++)
		o.push_back(new Player((char*)"images/elves.png", 100 * i, 200, (char*)"images/elves.txt", (char*)"player"));

	while (window.isOpen())
	{
		
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		sf:: Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf:: Event:: Closed)
				window.close();
		}


		if (sf::Keyboard:: isKeyPressed(sf::Keyboard:: Down))
		{
			o[0]->add_speed(0, 0.1);

			coordiantesForView(o[0]->getObjectCenterCoordinate(), &view);
		}

		if (sf::Keyboard:: isKeyPressed(sf::Keyboard:: Up))
		{
			o[0]->add_speed(0, -0.1);

			coordiantesForView(o[0]->getObjectCenterCoordinate(), &view);
		}

		if (sf::Keyboard:: isKeyPressed(sf::Keyboard:: Left))
		{
			o[0]->add_speed(-0.1, 0);

			coordiantesForView(o[0]->getObjectCenterCoordinate(), &view);
		}

		if (sf::Keyboard:: isKeyPressed(sf::Keyboard:: Right))
		{
			o[0]->add_speed(0.1, 0);

			coordiantesForView(o[0]->getObjectCenterCoordinate(), &view);
		}



		//window.setView(view);

		window.clear();
		
		for (auto x:o)
		{
			x->update(time, &window);
		}
		//o->update(time, &window);
/*
		for (int i = 0; i < objects.size(); i++)
		{
			//if (GameObject temp = dynamic_cast<GameObject> (*objects[i]))
				objects[i]->update(time, &window);
		}
*/
		window.display();
	}

	
	
	return 0;
}