#ifndef CHUNK_H
#define CHUNK_H

#include <iostream>
#include <vector>
#include <array>
#include <GL/glut.h>
#include "block.h"

class Chunk
{
  
public:
  static const short dim = 16;
  static const short volume = 16 * 16 * 16;

  Chunk(int x = 0, int y = 0, int z = 0);
  Chunk(std::array<int, 3> origin);

  
  //by default these chunk don't hold drawing data
  //because they don't know of each other and are drawn
  //as if each chunk is the only one
  //chunks compute all chukn edges visible and this is not needed by default
  //following methods are provided primary for testing
  std::vector<int>& visibleBlocks(std::vector<int> &visibleBlocks) const;
  void toVertArray(const std::vector<int>&visibleBlocks, std::vector<int> &verts, std::vector<float> &colors);
  void pushVisible(std::vector<int> &visibleBlocks, int i, short faces) const;
  void drawArrays(const std::vector<int> &verts, const std::vector<float> &colors) const;

  

  void fill(Block::Type b);
  bool isEdgeBlock(int i) const;
  void draw(std::vector<int>&visibleBlocks) const;

private:
  std::array<int, 3> m_origin;
  std::array<Block::Type, Chunk::volume> m_blocks;
};

#endif // CHUNK_H

