#include "game.h"

Game::Game()
  : m_window(sf::VideoMode(800, 600),
	     "Zombie",
	     sf::Style::Default, sf::ContextSettings(32))
{
  m_window.setVerticalSyncEnabled(true);
  m_window.setActive(true);
  
  // load resources, initialize the OpenGL states, ...
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
  }
}

void Game::update(const sf::Time & timePerFrame)
{
  // to do ..
}

void Game::render()
{
  // clear the buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Draw hire:

  glColor3f(0, 0, 1);
  glBegin(GL_POLYGON);
      glVertex3f(0.5, -0.5, 0);
      glVertex3f(-0.5, -0.5, 0);
      glVertex3f(-0.5, 0.5, 0);
      glVertex3f(0.5, 0.5, 0);
  glEnd();

  glColor3f(0, 0.5, 0);
  glBegin(GL_POLYGON);
      glVertex3f(-0.9, -0.9, 0);
      glVertex3f(-0.9, -0.5, 0);
      glVertex3f(-0.5, -0.9, 0);
  glEnd();

  glColor3f(1, 0, 0);
  glBegin(GL_POLYGON);
      glVertex3f(0.9, 0.9, 0);
      glVertex3f(0.9, 0.5, 0);
      glVertex3f(0.5, 0.9, 0);
  glEnd();
  
  m_window.display();
}
