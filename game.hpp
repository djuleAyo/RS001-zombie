#ifndef GAME_HPP
#define GAME_HPP

class Game {
  public:
    /**
     * @brief run
     * Pokrece igru
     */
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
