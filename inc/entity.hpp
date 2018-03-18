#pragma once

#include <array>
/*
 * This class is base of inheritance chain.
 * Entity has a mash that can be drawn. To not confuse object with programming
 * objcts we call it entity.
 */
class Entity
{
public:
  Entity(double x, double y, double z);

  virtual void draw() const/* = 0*/;
  virtual ~Entity() {}

protected:

  std::array<double, 3> m_position;
};
