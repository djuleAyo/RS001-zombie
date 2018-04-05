#ifndef ENTITY_H
#define ENTITY_H

#include <array>
/*
 * This class is base of inheritance chain.
 * Entity has a mash that can be drawn. To not confuse object with programming
 * objcts we call it entity.
 */
class Entity
{
public:
  Entity(double x = 0, double y = 0, double z = 0);

  virtual void draw() const/* = 0*/;
  virtual ~Entity() {}

protected:

  std::array<double, 3> m_position;
};

#endif // ENTITY_H
