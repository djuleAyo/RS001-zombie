#include "game.h"
#include "chunk.h"
#include "map.h"
#include "camera.h"
#include "input.h"

#include <iostream>

Map map {std::string("hello zombie"), 2, std::array<int, 3>{0, 0, 0}};
Camera camera;
Input input;

Game::Game()
  : m_window(sf::VideoMode(1600, 900),
	     "Zombie",
	     sf::Style::Default, sf::ContextSettings(32))
{
  m_window.setVerticalSyncEnabled(true);
  m_window.setActive(true);
  
  // load resources, initialize the OpenGL states, ...

  //set the projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, 1600 / (float) 900, 1, 1000);
  glMatrixMode(GL_MODELVIEW);

  //glCullFace(GL_FRONT);
  glDisable(GL_CULL_FACE);
  
  //don't need the repeat
  m_window.setKeyRepeatEnabled(false);
  //don't need native cursor
  m_window.setMouseCursorVisible(false);
}

void Game::run(unsigned minimumFramePerSeconds)
{
  // game loop:
  sf::Clock clock;
  sf::Time timeSinceLastUpdate;
  const sf::Time timePerFrame = sf::seconds(1.f / minimumFramePerSeconds);

  while (m_window.isOpen()) {
    processEvents();
    timeSinceLastUpdate = clock.restart();
    while (timeSinceLastUpdate > timePerFrame) {
      timeSinceLastUpdate -= timePerFrame;
      update(timePerFrame);
    }
    update(timeSinceLastUpdate);
    render();
  }
}

void Game::processEvents()
{
  sf::Event event;
  while (m_window.pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      m_window.close();
    else if(event.type == sf::Event::Resized)
      glViewport(0, 0, event.size.width, event.size.height);
    
    // Here we will read inputs

    //mouse
    sf::Vector2i localPosition = sf::Mouse::getPosition(m_window);

    if(localPosition.x != 800)
      input.mouseX(localPosition.x - 800);

    if(localPosition.y != 450)
      input.mouseY(450 - localPosition.y);

    if(localPosition.x != 800 || localPosition.y != 450)
    sf::Mouse::setPosition(sf::Vector2i(800, 450), m_window);


    //keyboard
    if (event.type == sf::Event::KeyPressed){
      if (event.key.code == sf::Keyboard::Escape){
	std::cout << "the escape key was pressed" << std::endl;
	std::cout << "control:" << event.key.control << std::endl;
	std::cout << "alt:" << event.key.alt << std::endl;
	std::cout << "shift:" << event.key.shift << std::endl;
	std::cout << "system:" << event.key.system << std::endl;
      }
      if (event.key.code == sf::Keyboard::O) {
	input.store('o', 0, 0);
      }
      if (event.key.code == sf::Keyboard::U) {
	input.store('U', 0, 0);
      }
      if (event.key.code == sf::Keyboard::Period) {
	input.store('.', 0, 0);
      }
      if (event.key.code == sf::Keyboard::E) {
	input.store('E', 0, 0);
      }
      if (event.key.code == sf::Keyboard::Space) {
	input.store(' ', 0, 0);
      }
      if (event.key.code == sf::Keyboard::J) {
	input.store('j', 0, 0);
      }
      

    }
    if(event.type == sf::Event::KeyReleased) {
      if (event.key.code == sf::Keyboard::O) {
	input.release('o', 0, 0);
      }
      if (event.key.code == sf::Keyboard::U) {
	input.release('U', 0, 0);
      }
      if (event.key.code == sf::Keyboard::Period) {
	input.release('.', 0, 0);
      }
      if (event.key.code == sf::Keyboard::E) {
	input.release('E', 0, 0);
      }
      if (event.key.code == sf::Keyboard::Space) {
	input.release(' ', 0, 0);
      }
      if (event.key.code == sf::Keyboard::J) {
	input.release('j', 0, 0);
      }
    }
  }
}

void Game::update(const sf::Time & timePerFrame)
{
  //keyboard input
  for(auto c : input.keys()) {
    switch(c) {
    case 'o':
      camera.left();
      break;
    case 'u':
      camera.right();
      break;
    case 'e':
      camera.back();
      break;
    case '.':
      camera.forward();
      break;
    case 'j':
      camera.down();
      break;
    case ' ':
      camera.up();
      break;
    }
  }
  //mouse input
  int curX = input.mouseX();
  int curY = input.mouseY();
  if(curX) {
    camera.aimFi(curX);
    input.mouseX(0);
  }
  if(curY) {
    camera.aimTheta(curY);
    input.mouseY(0); 
  }
  camera.setAim();
}

void Game::render()
{
  // clear the buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Draw hire:

  map.draw(camera);
  
  m_window.display();
}
