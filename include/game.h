#ifndef GAME_H
#define GAME_H

class Game {
  public:
    /**
     * @brief run
     * Pokrece igru
     */
    Game();
    void run();

  private:
    /**
     * @brief processEvents
     * obradjuje komande
     */
    void processEvents();

    void update();

    void render();

};

#endif // GAME_HPP
