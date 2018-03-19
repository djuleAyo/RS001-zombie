#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <GL/glut.h>
#include "block.hpp"

class Chunk
{
  
public:
  static const short dim = 16;
  static const short volume = 16 * 16 * 16;

  //by default these chunk don't hold drawing data
  //because they don't know of each other and are drawn
  //as if each chunk is the only one
  //chunks compute all chukn edges visible and this is not needed by default
  //following methods are provided primary for testing
  std::vector<int>& visibleBlocks(std::vector<int> &visibleBlocks);
  void toVertArray(const std::vector<int>&visibleBlocks, std::vector<int> &verts, std::vector<float> &colors);
  void pushVisible(std::vector<int> &visibleBlocks, int i, short faces);
  void drawArrays(std::vector<int> &verts, std::vector<float> &colors);

  
  Chunk(int x, int y, int z);
  void fill(Block::Type b);
  bool isEdgeBlock(int i) const;
  void draw(std::vector<int>&visibleBlocks);

private:
  std::array<int, 3> m_origin;
  std::array<Block::Type, Chunk::volume> m_blocks;
};

