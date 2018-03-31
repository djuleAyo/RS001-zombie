#pragma once
#include <vector>
#include <GL/glut.h>


class Block
{
public:
  enum Type
    {
      //AIR must be 0
      AIR = 0,
      SOIL,
    };

  //this is to be used as bit flags
  enum VisibleFace
    {
      NONE = 0,
      UP = 1,
      DOWN = 2,
      NORTH = 4,
      SOUTH = 8,
      WEST = 16,
      EAST = 32,
      ALL = 64
    };

public:
  static void drawVisibleFaces(short faces);
  static void toVertArray(int originX, int originY, int originZ, short faces,
			      std::vector<int> &verts_out,
			      std::vector<float> &colors_out);

};
