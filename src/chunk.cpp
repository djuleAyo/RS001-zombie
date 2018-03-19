#include "chunk.hpp"

Chunk::Chunk(int x, int y, int z)
{
  m_origin[0] = x;
  m_origin[1] = y;
  m_origin[2] = z;

  fill(Block::SOIL);

}
void Chunk::fill(Block b)
{
  for(int i = 0; i < Chunk::volume; i++)
    m_blocks[i] = b;
  visibleBlocks();
}
std::vector<int>& Chunk::visibleBlocks()
{
  m_visibleBlocks.clear();
  for( int i = 0; i < Chunk::volume; i++) {

    if(!m_blocks[i]) continue;
    //sentinel: eliminate edges to always access all 6 sides
    //makes sense since chunk doesn't know of other chunks so it assumes
    // all edge blocks are visible
    if(isEdgeBlock(i)) {
      pushVisible(i);
      continue;
    }
    int x = i % Chunk::dim;
    int y = (i / Chunk::dim) % Chunk::dim;
    int z = i / (Chunk::dim * Chunk::dim);

      
    if(!m_blocks[x + 1 + y * Chunk::dim + z * Chunk::dim * Chunk::dim]
       || !m_blocks[x - 1 + y * Chunk::dim + z * Chunk::dim * Chunk::dim]
       || !m_blocks[x + (y + 1) * Chunk::dim + z * Chunk::dim * Chunk::dim]
       || !m_blocks[x + (y - 1) * Chunk::dim + z * Chunk::dim * Chunk::dim]
       || !m_blocks[x + y * Chunk::dim + (z - 1) * Chunk::dim * Chunk::dim]
       || !m_blocks[x + y * Chunk::dim + (z + 1) * Chunk::dim * Chunk::dim]
       )
      pushVisible(i);
      
  }
  return m_visibleBlocks;
}
void Chunk::pushVisible(int i)
{
  m_visibleBlocks.push_back(i % Chunk::dim);
  m_visibleBlocks.push_back( (i / Chunk::dim) % Chunk::dim);
  m_visibleBlocks.push_back(i / (Chunk::dim * Chunk::dim));
  m_visibleBlocks.push_back(static_cast<int>(m_blocks[i]));

}
bool Chunk::isEdgeBlock(int i) const
{
  if( i % Chunk::dim == 0
      || i % Chunk::dim == Chunk::dim - 1
      || (i / Chunk::dim) % Chunk::dim == 0
      || (i / Chunk::dim) % Chunk::dim == Chunk::dim - 1
      || (i / (Chunk::dim * Chunk::dim)) % Chunk::dim == 0
      || (i / (Chunk::dim * Chunk::dim)) % Chunk::dim == Chunk::dim - 1
      ) return true;
  return false;
}
void Chunk::draw()
{
  glPushMatrix();
  glTranslatef(m_origin[0],
	       m_origin[1],
	       m_origin[2]);
    
  //dummy implemenation
  for(int i = 0; i < m_visibleBlocks.size(); i += 4) {
    glPushMatrix();
    glTranslatef(m_visibleBlocks[i],
		 m_visibleBlocks[i + 1],
		 m_visibleBlocks[i + 2]);
      

      

    glutWireCube(1);
    glPopMatrix();
		  
  }
  glPopMatrix();
}
