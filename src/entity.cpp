#include "include/entity.h"
#include <iostream>
#include <GL/glut.h>

Entity::Entity(double x, double y, double z)
{
  m_position[0] = x;
  m_position[1] = y;
  m_position[2] = z;
}

void Entity::draw() const
{
  
  glutWireCube(.5);
}
