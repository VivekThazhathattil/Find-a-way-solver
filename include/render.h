#include <SFML/Graphics.hpp>
#include "consts.h"
#include "position.h"
#include <vector>
#include "env.h"

class Render{
	private:
		Env env;
    		sf::RenderWindow window;
		std::vector<sf::CircleShape> circles;
		std::vector<sf::RectangleShape> rects;
		std::vector<sf::RectangleShape> lines;

		void createDrawables();
		void resetRender();
		ScreenPos getScreenLocFromPos(Pos& pos);
		void createRects();
		void createCircles();
		void drawNDisplayDrawables();
	public:
		Render();
		~Render();
		void runSimulation();
};
