#ifndef INPUT_H
#define INPUT_H

#include <set>
#include <chrono>
#include <iostream>

class Input
{
public:
  void store(unsigned char c, int x, int y);
  void release(unsigned char c, int x, int y);
  void print();
  void windowW(int x);
  void windowH(int x);
  int windowW();
  int windowH();
  void mouseX(int x);
  void mouseY(int y);
  int mouseX();
  int mouseY();
  std::set<char>& keys();
private:
  int m_mouseX, m_mouseY;
  int m_windowW, m_windowH;
  std::set<char> m_keys;
};

#endif // INPUT_H
