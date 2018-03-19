#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <GL/glut.h>

enum Block
  {
    //AIR must be 0
    AIR = 0,
    SOIL,
  };

class Chunk
{
  
public:
  static const short dim = 16;
  static const short volume = 16 * 16 * 16;

  
  Chunk(int x, int y, int z);
  void fill(Block b);
  std::vector<int>& visibleBlocks();
  void pushVisible(int i);
  bool isEdgeBlock(int i) const;
  void draw();
private:
  std::array<int, 3> m_origin;
  std::array<Block, Chunk::volume> m_blocks;
  std::vector<int> m_visibleBlocks;
};
