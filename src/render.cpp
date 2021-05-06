#include "../include/render.h"

Render::Render() : window(sf::RenderWindow(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Find a way solver!", sf::Style::Close)) {}
Render::~Render() {}

void Render::runSimulation(){
	window.setPosition(sf::Vector2i(100,100));
	createDrawables();
	while(window.isOpen()){
		sf::Event e;
		while(window.pollEvent(e)){
			switch(e.type){
				case sf::Event::Closed:
	                                window.close();
					break;
				case sf::Event::KeyPressed:
					if(e.key.code == sf::Keyboard::R){
						env.resetEnv();
						resetRender();
					}
				case sf::Event::MouseButtonPressed:
					if (e.mouseButton.button == sf::Mouse::Left){
					}
				default:
					break;
			}
		}	

		// do something!
		window.clear(sf::Color::White);	
		drawNDisplayDrawables();
	}
}

void Render::createDrawables(){
//	sf::RenderTarget::clear(sf::Color::White);
	createRects();
	createCircles();
}

void Render::drawNDisplayDrawables(){
	for(int i = 0; i < circles.size(); i++)
		window.draw(circles[i]);
	for(int i = 0; i < rects.size(); i++)
		window.draw(rects[i]);
	window.display();
}

void Render::createRects(){
	for(int i = 0; i < env.obstacles.size(); i++){
		sf::RectangleShape rect;
		rect.setFillColor(sf::Color::Black);
		rect.setSize(sf::Vector2f(RECT_SIZE, RECT_SIZE));
		rect.setOrigin(sf::Vector2f(RECT_SIZE/2,RECT_SIZE/2));
		ScreenPos scrPos = getScreenLocFromPos(env.obstacles[i]);
		rect.setPosition(sf::Vector2f(scrPos.x,scrPos.y));
		rects.push_back(rect);
	}
}

void Render::createCircles(){
	for(int i = 0; i < env.dots.size(); i++){
		sf::CircleShape circle;
		Pos pos = env.getPosFromGridId(env.dots[i]);
		if(env.startPos.x == pos.x && env.startPos.y == pos.y)
			circle.setFillColor(sf::Color(233,76,111)); //grey
		else
			circle.setFillColor(sf::Color(204,204,204)); //pink
		circle.setRadius(float(RECT_SIZE/2));
		circle.setOrigin(sf::Vector2f(RECT_SIZE/2,RECT_SIZE/2));
		ScreenPos scrPos = getScreenLocFromPos(pos);
		circle.setPosition(sf::Vector2f(scrPos.x,scrPos.y));
		circles.push_back(circle);
	}
}

ScreenPos Render::getScreenLocFromPos(Pos& pos){
	Pos offset = {(int)((window.getSize().x - env.n*GRID_SPACING)/2),\
			(int)((window.getSize().y - env.m*GRID_SPACING))/2}; 

	Pos screenLoc = { offset.x + pos.x*GRID_SPACING + GRID_SPACING/2, offset.y + pos.y*GRID_SPACING + GRID_SPACING/2};
	return screenLoc;
}

void Render::resetRender(){
	circles.clear();	
	rects.clear();
	lines.clear();
	window.clear(sf::Color::White);	
	createDrawables();
}
