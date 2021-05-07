#include "../include/render.h"
#include <iostream>

Render::Render() : window(sf::RenderWindow(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Find a way solver!", sf::Style::Close)) {}
Render::~Render() {}

void Render::runSimulation(){
	bool isPaused = false;
	bool solutionMode = false;
	bool solverMode = false;
	bool solverSolutionMode = false;
	window.setPosition(sf::Vector2i(100,100));
	do{
		env.resetEnv();
		resetRender();
	}while(!isProblemSolvable());
	while(window.isOpen()){
		sf::Event e;
		window.clear(sf::Color::White);	
		while(window.pollEvent(e)){
			switch(e.type){
				case sf::Event::Closed:
	                                window.close();
					break;
				case sf::Event::KeyPressed:
					if(e.key.code == sf::Keyboard::R){
						do{
							env.resetEnv();
							resetRender();
						}while(!isProblemSolvable());
					}
					else if (e.key.code == sf::Keyboard::S){
						if(!solutionMode){
							solutionMode = true;
							showSolution();
						}
						else{
							solutionMode = false;
							lines.clear();
							//reset circle colors
							for(int i = 0; i < circles.size(); i++)
								circles[i].setFillColor(sf::Color(204,204,204)); 
							// find the circle which matches the starting pos
							for (int i = 0; i < env.dots.size(); i++){
								if(env.getGridIdFromPos(env.startPos) == env.dots[i])
									circles[i].setFillColor(sf::Color(233,76,111));
							}
						}
					}
					else if (e.key.code == sf::Keyboard::C){
						if(!solverMode){
							solverMode = true;
							std::cout << "Hello\n";
							getSolverMode();
						}
						else{
							solverMode = false;
							solutionMode = false;
							purgeSolverMode();
						}
					}

					else if (e.key.code == sf::Keyboard::V){
						if(!solverSolutionMode){
							solverSolutionMode = true;
							bool temp = isProblemSolvable();
							showSolution();
						}
						else{
							solverSolutionMode = false;
							for(int i = 0; i < circles.size(); i++)
								circles[i].setFillColor(sf::Color(204,204,204)); 
							// find the circle which matches the starting pos
							for (int i = 0; i < env.dots.size(); i++){
								if(env.getGridIdFromPos(env.startPos) == env.dots[i])
									circles[i].setFillColor(sf::Color(233,76,111));
							}
						}
					}
				case sf::Event::MouseButtonPressed:
					if (e.mouseButton.button == sf::Mouse::Left){
					}
				case sf::Event::LostFocus:
					isPaused = true;
				case sf::Event::GainedFocus:
					isPaused = false;
				default:
					break;
			}
		}	
		if(!isPaused)
			drawNDisplayDrawables();
	}
}

void Render::createDrawables(){
//	sf::RenderTarget::clear(sf::Color::White);
	createRects();
	createCircles();
}

void Render::drawNDisplayDrawables(){
	for(int i = 0; i < lines.size(); i++)
		window.draw(lines[i]);
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
			circle.setFillColor(sf::Color(233,76,111)); //pink
		else
			circle.setFillColor(sf::Color(204,204,204)); //grey
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
//	window.clear(sf::Color::White);	
	createDrawables();
}

bool Render::isProblemSolvable(){
	return env.getHamiltonianPath();
}

void Render::showSolution(){
	sf::RectangleShape  rect;
	rect.setFillColor(sf::Color(233,76,111)); //pink
	for(int i = 0; i < env.path.size()-1; i++){
		Pos posFirst = env.getPosFromGridId(env.path[i]);
		Pos posSecond = env.getPosFromGridId(env.path[i+1]);
		ScreenPos pos0 = getScreenLocFromPos(posFirst);
		ScreenPos pos1 = getScreenLocFromPos(posSecond);
		rect.setPosition(sf::Vector2f(int((pos0.x+pos1.x)/2), int((pos0.y+pos1.y)/2)));
		if(pos0.x == pos1.x){ //vertical
			rect.setOrigin(sf::Vector2f(RECT_SIZE/4,GRID_SPACING/2));
			rect.setSize(sf::Vector2f(RECT_SIZE/2,GRID_SPACING));
		}
		else{ //horizontal
			rect.setOrigin(sf::Vector2f(GRID_SPACING/2,RECT_SIZE/4));
			rect.setSize(sf::Vector2f(GRID_SPACING,RECT_SIZE/2));
		}

		lines.push_back(rect);
	}
	for(int i = 0; i < circles.size(); i++)
		circles[i].setFillColor(sf::Color(233,76,111)); 
}

void Render::getSolverMode(){	
	window.clear();
	env.path.clear();	
	env.dots.clear();
	env.obstacles.clear();
	env.adjMat.clear();
	int numObstacles;

	std::cin >> env.m >> env.n >> numObstacles;

	Pos pos;
	for(int i = 0; i < numObstacles; i++){
		std::cin >> pos.x >> pos.y;
		env.obstacles.push_back(pos);
	}

	std::cin >> env.startPos.x >> env.startPos.y;

	for (int i = 0; i < env.m * env.n; i++)
	{
		Pos pos = env.getPosFromGridId(i);
		if(env.isGridFree(i))
		{ 
			env.dots.push_back(i);
		}
	}

	resetRender();	
}

void Render::purgeSolverMode(){

}
