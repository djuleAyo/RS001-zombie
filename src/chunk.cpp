#include "chunk.h"
#include <GL/glut.h>

Chunk::Chunk(int x, int y, int z)
{
  m_origin[0] = x;
  m_origin[1] = y;
  m_origin[2] = z;

  fill(Block::Type::SOIL);
}
Chunk::Chunk(std::array<int, 3> origin)
  :m_origin(origin)
{
  fill(Block::Type::SOIL);
}
void Chunk::fill(Block::Type b)
{
  for(int i = 0; i < Chunk::volume; i++)
    m_blocks[i] = b;
}
std::vector<int>& Chunk::visibleBlocks(std::vector<int> &visibleBlocks) const
{
  visibleBlocks.clear();
  for( int i = 0; i < Chunk::volume; i++) {

    if(!m_blocks[i]) continue;

    int x = i % Chunk::dim;
    int y = (i / Chunk::dim) % Chunk::dim;
    int z = i / (Chunk::dim * Chunk::dim);
    short faces = 0;
      
    if(x == 15 || !m_blocks[x + 1 + y * Chunk::dim + z * Chunk::dim * Chunk::dim])
      faces |= Block::VisibleFace::EAST;
    if(x == 0 || !m_blocks[x - 1 + y * Chunk::dim + z * Chunk::dim * Chunk::dim])
      faces |= Block::VisibleFace::WEST;
    if(y == 15 || !m_blocks[x + (y + 1) * Chunk::dim + z * Chunk::dim * Chunk::dim])
      faces |= Block::VisibleFace::UP;
    if(y == 0 || !m_blocks[x + (y - 1) * Chunk::dim + z * Chunk::dim * Chunk::dim])
      faces |= Block::VisibleFace::DOWN;
    if(z == 0 || !m_blocks[x + y * Chunk::dim + (z - 1) * Chunk::dim * Chunk::dim])
      faces |= Block::VisibleFace::NORTH;
    if(z == 15 || !m_blocks[x + y * Chunk::dim + (z + 1) * Chunk::dim * Chunk::dim])
      faces |= Block::VisibleFace::SOUTH;

    pushVisible(visibleBlocks, i, faces);
      
  }
  return visibleBlocks;
}

//m_origin in this function are bound to instance but vectors passed are not! This allows us to switch positions to chukns
//which is neat
void Chunk::toVertArray(const std::vector<int> &visibleBlocks, std::vector<int> &verts, std::vector<float> &colors)
{

  for(int i = 0; i < visibleBlocks.size(); i += 4) {
    Block::toVertArray(m_origin[0] + visibleBlocks[i],
		    m_origin[1] + visibleBlocks[i + 1],
		    m_origin[2] + visibleBlocks[i + 2],
		    visibleBlocks[i + 3],
		    verts, colors
		    );
  }
}
void Chunk::drawArrays(const std::vector<int> &verts, const std::vector<float> &colors) const
{
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  
  glVertexPointer(3, GL_INT, 0, verts.data());
  glColorPointer(3, GL_FLOAT, 0, colors.data());

  glDrawArrays(GL_QUADS, 0, verts.size() / 3);

}
void Chunk::pushVisible(std::vector<int> &visibleBlocks,int i, short faces) const
{
  visibleBlocks.push_back(i % Chunk::dim);
  visibleBlocks.push_back( (i / Chunk::dim) % Chunk::dim);
  visibleBlocks.push_back(i / (Chunk::dim * Chunk::dim));
  visibleBlocks.push_back(static_cast<int>(faces));

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
void Chunk::draw(std::vector<int> &visibleBlocks) const
{
  glPushMatrix();
  glTranslatef(m_origin[0],
	       m_origin[1],
	       m_origin[2]);
    
  //dummy implemenation
  for(int i = 0; i < visibleBlocks.size(); i += 4) {
    glPushMatrix();
    glTranslatef(visibleBlocks[i],
		 visibleBlocks[i + 1],
		 visibleBlocks[i + 2]);
      
    Block::drawVisibleFaces(visibleBlocks[i + 3]);
    glPopMatrix();
		  
  }
  glPopMatrix();
}
