#ifndef GAME_H
#define GAME_H

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>


class Game
{    
public:
  Game();
  Game(const Game &) = delete;
  Game & operator = (const Game &) = delete;
  void run(unsigned);
  
private:
  void processEvents();
  void update(const sf::Time &);
  void render();
  
  sf::Window m_window;
};

#endif // GAME_H
