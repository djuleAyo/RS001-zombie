#include "chunk.hpp"
#include <GL/glut.h>

Chunk::Chunk(int x, int y, int z)
{
  m_origin[0] = x;
  m_origin[1] = y;
  m_origin[2] = z;

  fill(Block::Type::SOIL);
  visibleBlocks();
  toVertArray();
}
void Chunk::fill(Block::Type b)
{
  for(int i = 0; i < Chunk::volume; i++)
    m_blocks[i] = b;
}
std::vector<int>& Chunk::visibleBlocks()
{
  m_visibleBlocks.clear();
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

    pushVisible(i, faces);
      
  }
  return m_visibleBlocks;
}

void Chunk::toVertArray()
{
  //must be called after visibleBlocks
  for(int i = 0; i < m_visibleBlocks.size(); i += 4) {
    cubeToVertArray(m_origin[0] + m_visibleBlocks[i],
		    m_origin[1] + m_visibleBlocks[i + 1],
		    m_origin[2] + m_visibleBlocks[i + 2],
		    m_visibleBlocks[i + 3],
		    m_verts, m_colors
		    );
  }
}
void Chunk::drawArrays()
{
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  
  glVertexPointer(3, GL_INT, 0, m_verts.data());
  glColorPointer(3, GL_FLOAT, 0, m_colors.data());

  glDrawArrays(GL_QUADS, 0, m_verts.size() / 3);

}
void Chunk::pushVisible(int i, short faces)
{
  m_visibleBlocks.push_back(i % Chunk::dim);
  m_visibleBlocks.push_back( (i / Chunk::dim) % Chunk::dim);
  m_visibleBlocks.push_back(i / (Chunk::dim * Chunk::dim));
  m_visibleBlocks.push_back(static_cast<int>(faces));

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
      
    drawVisibleFaces(m_visibleBlocks[i + 3]);
    glPopMatrix();
		  
  }
  glPopMatrix();
}


void drawVisibleFaces(short faces)
{

  //NOTE: in ogl positive z goes to camera
  //meaning north and south are fliped!
  if(faces & Block::VisibleFace::UP) {
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glVertex3i(0, 1, 0);
    glVertex3i(0, 1, 1);
    glVertex3i(1, 1, 1);
    glVertex3i(1, 1, 0);
    glEnd();
  }
  if(faces & Block::VisibleFace::DOWN) {
    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex3i(0, 0, 0);
    glVertex3i(0, 0, 1);
    glVertex3i(1, 0, 1);
    glVertex3i(1, 0, 0);
    glEnd();
  }
  if(faces & Block::VisibleFace::NORTH) {
    glColor3f(0, 0, 1);
    glBegin(GL_QUADS);
    glVertex3i(0, 0, 0);
    glVertex3i(0, 1, 0);
    glVertex3i(1, 1, 0);
    glVertex3i(1, 0, 0);
    glEnd();
  }
  if(faces & Block::VisibleFace::SOUTH) {
    glColor3f(0, 1, 1);
    glBegin(GL_QUADS);
    glVertex3i(0, 0, 1);
    glVertex3i(0, 1, 1);
    glVertex3i(1, 1, 1);
    glVertex3i(1, 0, 1);
    glEnd();
  }
  if(faces & Block::VisibleFace::WEST) {
    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    glVertex3i(0, 0, 0);
    glVertex3i(0, 0, 1);
    glVertex3i(0, 1, 1);
    glVertex3i(0, 1, 0);
    glEnd();
  }
  if(faces & Block::VisibleFace::EAST) {
    glColor3f(0, 1, 0);
    glBegin(GL_QUADS);
    glVertex3i(1, 0, 0);
    glVertex3i(1, 0, 1);
    glVertex3i(1, 1, 1);
    glVertex3i(1, 1, 0);
    glEnd();
  }

}

void cubeToVertArray(int originX, int originY, int originZ, short faces,
		     std::vector<int> &verts_out, std::vector<float>&colors_out)
{
  std::vector<int> *verts = new std::vector<int>;
  
  if(faces & Block::VisibleFace::UP) {
    verts_out.push_back(originX + 0); verts_out.push_back(originY + 1); verts_out.push_back(originZ + 0);
    colors_out.push_back(1); colors_out.push_back(0); colors_out.push_back(0);
    verts_out.push_back(originX + 0); verts_out.push_back(originY + 1); verts_out.push_back(originZ + 1);
    colors_out.push_back(1); colors_out.push_back(0); colors_out.push_back(1);
    verts_out.push_back(originX + 1); verts_out.push_back(originY + 1); verts_out.push_back(originZ + 1);
    colors_out.push_back(1); colors_out.push_back(1); colors_out.push_back(0);
    verts_out.push_back(originX + 1); verts_out.push_back(originY + 1); verts_out.push_back(originZ + 0);
    colors_out.push_back(1); colors_out.push_back(1); colors_out.push_back(1);
  }
  if(faces & Block::VisibleFace::DOWN) {
    verts_out.push_back(originX + 0); verts_out.push_back(originY + 0); verts_out.push_back(originZ + 0);
    colors_out.push_back(0); colors_out.push_back(0); colors_out.push_back(0);
    verts_out.push_back(originX + 0); verts_out.push_back(originY + 0); verts_out.push_back(originZ + 1);
    colors_out.push_back(0); colors_out.push_back(0); colors_out.push_back(1);
    verts_out.push_back(originX + 1); verts_out.push_back(originY + 0); verts_out.push_back(originZ + 1);
    colors_out.push_back(0); colors_out.push_back(1); colors_out.push_back(0);
    verts_out.push_back(originX + 1); verts_out.push_back(originY + 0); verts_out.push_back(originZ + 0);
    colors_out.push_back(0); colors_out.push_back(1); colors_out.push_back(1);
  }
  if(faces & Block::VisibleFace::NORTH) {
    verts_out.push_back(originX + 0); verts_out.push_back(originY + 0); verts_out.push_back(originZ + 0);
    colors_out.push_back(1); colors_out.push_back(0); colors_out.push_back(0);
    verts_out.push_back(originX + 0); verts_out.push_back(originY + 1); verts_out.push_back(originZ + 0);
    colors_out.push_back(1); colors_out.push_back(0); colors_out.push_back(1);
    verts_out.push_back(originX + 1); verts_out.push_back(originY + 1); verts_out.push_back(originZ + 0);
    colors_out.push_back(1); colors_out.push_back(1); colors_out.push_back(0);
    verts_out.push_back(originX + 1); verts_out.push_back(originY + 0); verts_out.push_back(originZ + 0);
    colors_out.push_back(1); colors_out.push_back(1); colors_out.push_back(1);
  }
  if(faces & Block::VisibleFace::SOUTH) {
    verts_out.push_back(originX + 0); verts_out.push_back(originY + 0); verts_out.push_back(originZ + 1);
    colors_out.push_back(0); colors_out.push_back(0); colors_out.push_back(0);
    verts_out.push_back(originX + 0); verts_out.push_back(originY + 1); verts_out.push_back(originZ + 1);
    colors_out.push_back(0); colors_out.push_back(0); colors_out.push_back(1);
    verts_out.push_back(originX + 1); verts_out.push_back(originY + 1); verts_out.push_back(originZ + 1);
    colors_out.push_back(0); colors_out.push_back(1); colors_out.push_back(0);
    verts_out.push_back(originX + 1); verts_out.push_back(originY + 0); verts_out.push_back(originZ + 1);
    colors_out.push_back(0); colors_out.push_back(1); colors_out.push_back(1);
  }
  if(faces & Block::VisibleFace::WEST) {
    verts_out.push_back(originX + 0); verts_out.push_back(originY + 0); verts_out.push_back(originZ + 0);
    colors_out.push_back(1); colors_out.push_back(0); colors_out.push_back(0);
    verts_out.push_back(originX + 0); verts_out.push_back(originY + 0); verts_out.push_back(originZ + 1);
    colors_out.push_back(1); colors_out.push_back(0); colors_out.push_back(1);
    verts_out.push_back(originX + 0); verts_out.push_back(originY + 1); verts_out.push_back(originZ + 1);
    colors_out.push_back(1); colors_out.push_back(1); colors_out.push_back(0);
    verts_out.push_back(originX + 0); verts_out.push_back(originY + 1); verts_out.push_back(originZ + 0);
    colors_out.push_back(1); colors_out.push_back(1); colors_out.push_back(1);
  }
  if(faces & Block::VisibleFace::EAST) {
    verts_out.push_back(originX + 1); verts_out.push_back(originY + 0); verts_out.push_back(originZ + 0);
    colors_out.push_back(0); colors_out.push_back(0); colors_out.push_back(0);
    verts_out.push_back(originX + 1); verts_out.push_back(originY + 0); verts_out.push_back(originZ + 1);
    colors_out.push_back(0); colors_out.push_back(0); colors_out.push_back(1);
    verts_out.push_back(originX + 1); verts_out.push_back(originY + 1); verts_out.push_back(originZ + 1);
    colors_out.push_back(0); colors_out.push_back(1); colors_out.push_back(0);
    verts_out.push_back(originX + 1); verts_out.push_back(originY + 1); verts_out.push_back(originZ + 0);
    colors_out.push_back(0); colors_out.push_back(1); colors_out.push_back(1);
  }

}

