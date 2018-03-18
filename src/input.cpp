#include "input.hpp"

void Input::store(unsigned char c, int x, int y)
{
  if(c >= 'A' && c <= 'Z')
    c += 'a' - 'A';
  m_keys.insert(c);
}

void Input::print()
{
  for(auto c : m_keys)
    std::cout << c << " ";
  std::cout << std::endl;
}

void Input::release(unsigned char c, int x, int y)
{
  if(c >= 'A' && c <= 'Z')
    c += 'a' - 'A';

  m_keys.erase(c);
}

std::set<char>& Input::keys()
{
  return m_keys;
}

int Input::windowW()
{
  return m_windowW; 
}
int Input::windowH()
{
  return m_windowH; 
}
void Input::windowW(int x)
{
  m_windowW = x;
}
void Input::windowH(int x)
{
  m_windowH = x;
}

void Input::mouseX(int x)
{
  m_mouseX = x;
}
void Input::mouseY(int y)
{
  m_mouseY = y;
}


int Input::mouseX()
{
  return m_mouseX;
}
int Input::mouseY()
{
  return m_mouseY;
}
