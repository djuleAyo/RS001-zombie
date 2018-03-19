#pragma once

#include <iostream>
#include <vector>
#include <array>
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
};

class Chunk
{
  
public:
  static const short dim = 16;
  static const short volume = 16 * 16 * 16;

  
  Chunk(int x, int y, int z);
  void fill(Block::Type b);
  std::vector<int>& visibleBlocks();
  void toVertArray();
  void pushVisible(int i, short faces);
  bool isEdgeBlock(int i) const;
  void draw();
  void drawArrays();
private:
  std::array<int, 3> m_origin;
  std::array<Block::Type, Chunk::volume> m_blocks;
  std::vector<int> m_visibleBlocks;
  std::vector<int> m_verts;
  std::vector<float> m_colors;
};

void drawVisibleFaces(short faces);
void cubeToVertArray(int originX, int originY, int originZ, short faces, std::vector<int> &verts_out, std::vector<float>&colors_out);
