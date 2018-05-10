#ifndef MANU_H
#define MANU_H

#include <TGUI/TGUI.hpp>

class Manu
{
public:
  Manu();
  Manu(const Manu &) = delete;
  Manu & operator = (const Manu &) = delete;
  void show();

private:
  void loadWidgets(tgui::Gui &);
  
  sf::RenderWindow m_window;
  tgui::Gui m_gui;
};


#endif // MANU_H
